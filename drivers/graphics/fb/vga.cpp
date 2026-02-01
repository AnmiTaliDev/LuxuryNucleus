/* 
VGA text framebuffer driver for legacy BIOS
*/

#define mmio_addr_vga_text_fb_colour     (volatile unsigned short*)0xB8000
#define mmio_addr_vga_text_fb_monochrome (volatile unsigned short*)0xB0000
#include <drivers/graphics/fb/vga.hpp>
#include <drivers/bda.hpp>
#include <library/libfb.hpp>
#include <general/logging/log.hpp>

volatile unsigned char  *const vga_graphics_buffer = (volatile unsigned char*)0xA0000;
Library::libfb::libfb   *vga_text_libfb;
volatile unsigned short *vga_text_buffer;

constexpr unsigned vga_width  = 80;
constexpr unsigned vga_height = 25;

void VGA::vga_text_fb::set_color(const enum vga_colors &foreground, const enum vga_colors &background)
{
    color_fg = foreground; color_bg = background;
    color = color_fg | color_bg << 4;
}

void VGA::vga_text_fb::put_entry(const unsigned short &entry) 
{
	vga_text_buffer[vga_text_libfb->D2toD1()] = entry;
}

void VGA::vga_text_fb::fill_with_zeros()
{
    for (vga_text_libfb->_rst_col(); vga_text_libfb->column != vga_width; vga_text_libfb->column++)
	    put_entry(0);
    vga_text_libfb->_rst_col();
}

/*void VGA::vga_text_fb::sync()
{
    unsigned row_pos, col_pos;
    for (vga_text_libfb->row = 0; vga_text_libfb->row != vga_height; vga_text_libfb->row++)
    {
        row_pos = vga_text_libfb->_calc_row_pos();
        for (vga_text_libfb->_rst_col(); vga_text_libfb->column != vga_width; vga_text_libfb->column++)
        {
            col_pos = row_pos + vga_text_libfb->column;
            vga_text_buffer[col_pos] = double_buffer[col_pos];
        }
    }
    vga_text_libfb->_rst_col();
}*/

void VGA::vga_text_fb::clean()
{
    set_color(LIGHT_GRAY, BLACK);
    for (vga_text_libfb->row = 0; vga_text_libfb->row != vga_height; vga_text_libfb->row++)
        fill_with_zeros();
    //sync();
}

void VGA::vga_text_fb::scroll()
{
    for (vga_text_libfb->row = 0; vga_text_libfb->row != vga_height; vga_text_libfb->row++)
    {
        for (vga_text_libfb->column = 0; vga_text_libfb->column != vga_width; vga_text_libfb->column++)
            scroll_row_buffer[vga_text_libfb->column] = vga_text_buffer[vga_text_libfb->D2toD1()];
        vga_text_libfb->row--;
        for (vga_text_libfb->column = 0; vga_text_libfb->column != vga_width; vga_text_libfb->column++)
            put_entry(scroll_row_buffer[vga_text_libfb->column]);
        vga_text_libfb->row++;
    }
    vga_text_libfb->row = 24;
    fill_with_zeros();
    //sync();
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
            put_entry((unsigned short)(what | color << 8));
            if (vga_text_libfb->column++ == vga_width)
                vga_text_libfb->newline();
            break;
    }
	if (vga_text_libfb->row == vga_height) scroll();
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
            static Library::libfb::libfb __vga_text_libfb(vga_width);
            vga_text_libfb = &__vga_text_libfb;
            unsigned short __scroll_row_buff[vga_text_libfb->width];
            scroll_row_buffer = __scroll_row_buff;
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