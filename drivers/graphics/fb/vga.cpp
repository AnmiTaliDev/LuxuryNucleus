/* 
VGA text framebuffer driver for legacy BIOS
*/

#include <drivers/bda.hpp>
#include <library/libfb.hpp>
#include <logging/log.hpp>

#define vga_text_width  80
#define vga_text_height 25

Library::libfb::libfb   *vga_text_libfb;
volatile unsigned short *vga_text_buffer;
unsigned short          *vga_text_scroll_buffer;

//volatile unsigned char  *const vga_graphics_buffer = mmio_addr_vga_graphics_fb;

void VGA::vga_text_fb::put_entry(const unsigned short &entry) 
{
	vga_text_buffer[vga_text_libfb->TwoDto1D()] = entry | attribute;
}

void VGA::vga_text_fb::fill_with_zeros()
{
    for (vga_text_libfb->_rst_col(); vga_text_libfb->column != vga_text_libfb->width; vga_text_libfb->column++)
	    put_entry(0);
    vga_text_libfb->_rst_col();
}

void VGA::vga_text_fb::set_attr(const enum vga_colors &foreground, const enum vga_colors &background, const bool &blink)
{
    attribute = (foreground | background << 4 | blink << 7) << 8;
}

void VGA::vga_text_fb::clean()
{
    set_attr(LIGHT_GRAY, BLACK, 0);
    for (vga_text_libfb->row = 0; vga_text_libfb->row != vga_text_libfb->height; vga_text_libfb->row++)
        fill_with_zeros();
    vga_text_libfb->row = 0;
}

void VGA::vga_text_fb::scroll()
{
    for (vga_text_libfb->row = 0; vga_text_libfb->row != vga_text_libfb->height; vga_text_libfb->row++)
    {
        for (vga_text_libfb->_rst_col(); vga_text_libfb->column != vga_text_libfb->width; vga_text_libfb->column++)
            vga_text_scroll_buffer[vga_text_libfb->column] = vga_text_buffer[vga_text_libfb->TwoDto1D()];
        vga_text_libfb->row--;
        for (vga_text_libfb->_rst_col(); vga_text_libfb->column != vga_text_libfb->width; vga_text_libfb->column++)
            put_entry(vga_text_scroll_buffer[vga_text_libfb->column]);
        vga_text_libfb->row++;
    }
    vga_text_libfb->row = 24;
    fill_with_zeros();
}

void VGA::vga_text_fb::put_char(const unsigned short &what)
{
    switch (what)
    {
        case '\r': 
            vga_text_libfb->_rst_col();
            break;
        case '\n':
            vga_text_libfb->newline();
            break;
        default:
            put_entry(what);
            if (vga_text_libfb->column++ == vga_text_libfb->width)
                vga_text_libfb->newline();
            break;
    }
	if (vga_text_libfb->row == vga_text_libfb->height) scroll();
}

VGA::vga_text_fb::vga_text_fb()
{
    enum BDA::video_type videotype = BDA::video_type();
    if (videotype != BDA::VIDEO_TYPE_NONE)
    {
        switch (videotype)
        {
            case BDA::VIDEO_TYPE_COLOUR:
                Logging::info("[vga/text]: detected colour video type");
                vga_text_buffer = mmio_addr_vga_text_fb_colour;
                break;
            case BDA::VIDEO_TYPE_MONOCHROME:
                Logging::info("[vga/text]: detected monochrome video type");
                vga_text_buffer = mmio_addr_vga_text_fb_monochrome;
                break;
            default:
                Logging::err("[vga/text]: failed to get video type");
                return;
        }
        Logging::info("[vga/text]: checking text mode fb size...");
        unsigned size = 0;
        while (vga_text_buffer[size])
            size++;
        if (size == 16388)
        {
            Logging::info("[vga/text]: initializing fb...");
            static Library::libfb::libfb __vga_text_libfb(vga_text_width,vga_text_height);
            vga_text_libfb = &__vga_text_libfb;
            static unsigned short __scroll_row_buff[80];
            vga_text_scroll_buffer = __scroll_row_buff;
            /*unsigned short __double_buff[16388];
            double_buffer = __double_buff;*/
            clean();
            init = true;
        }
        else if (size == 0)
            Logging::warn("[vga/text]: no text fb is allocated");
        else Logging::err("[vga/text]: invalid size");
    }
}
