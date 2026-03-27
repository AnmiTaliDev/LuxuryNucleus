/* 
VGA text framebuffer driver for legacy BIOS
*/

#include <drivers/bda.hpp>
#include <logging.hpp>
#include <mmio/get_ptr.hpp>
#include <mmio/alloc.hpp>
#include <drivers/graphics/gpu/fb/vga.hpp>
using namespace Drivers::Graphics::FB::VGA;

#define vga_text_width  80
#define vga_text_height 25

#define mmio_addr_vga_text_fb_colour     0xB8000
#define mmio_addr_vga_text_fb_monochrome 0xB0000
#define mmio_addr_vga_graphics_fb        0xA0000

//volatile unsigned char *const vga_graphics_buffer = mmio_addr_vga_graphics_fb;
volatile unsigned short *vga_text_buffer;
unsigned short *vga_text_scroll_buffer;

void vga_text_fb::put_entry(const unsigned short entry) 
{
	vga_text_buffer[Y * vga_text_width + X] = entry | attribute;
}

void vga_text_fb::fill_with_zeros()
{
    for (X = 0; X != vga_text_width; X++)
	    put_entry(0);
    X = 0;
}

void vga_text_fb::set_attr(const enum vga_colors &foreground, const enum vga_colors &background, const bool &blink)
{
    attribute = (foreground | background << 4 | blink << 7) << 8;
}

void vga_text_fb::clean()
{
    set_attr(LIGHT_GRAY, BLACK, 0);
    for (Y = 0; Y != vga_text_height; Y++)
        fill_with_zeros();
    Y = 0;
}

void vga_text_fb::scroll()
{
    for (Y = 0; Y != vga_text_height; Y++)
    {
        for (X = 0; X != vga_text_width; X++)
            vga_text_scroll_buffer[X] = vga_text_buffer[Y * vga_text_width + X];
        Y--;
        for (X = 0; X != vga_text_width; X++)
            put_entry(vga_text_scroll_buffer[X]);
        Y++;
    }
    Y = 24;
    fill_with_zeros();
}

void vga_text_fb::put_char(const unsigned short &what)
{
    switch (what)
    {
        case '\r': 
            X = 0;
            break;
        case '\n':
            X = 0;
            Y++;
            break;
        default:
            put_entry(what);
            if (X++ == vga_text_width)
            {
                X = 0;
                Y++;
            }
            break;
    }
	if (Y == vga_text_height) scroll();
}

vga_text_fb::vga_text_fb()
{
    Logging::info("[vga/text]: checking size...");
    unsigned long long size = 0;
    while (vga_text_buffer[size])
        size++;
    if (size > 1)
    {
        Logging::info("[vga/text]: checking video type in BDA...");
        enum BDA::video_type videotype = BDA::video_type();
        if (videotype != BDA::VIDEO_TYPE_NONE)
        {
            switch (videotype)
            {
                case BDA::VIDEO_TYPE_COLOUR:
                    Logging::info("[vga/text]: detected colour video type");
                    vga_text_buffer = ushort_ptr(mmio_addr_vga_text_fb_colour);
                    break;
                case BDA::VIDEO_TYPE_MONOCHROME:
                    Logging::info("[vga/text]: detected monochrome video type");
                    vga_text_buffer = ushort_ptr(mmio_addr_vga_text_fb_monochrome);
                    break;
                default:
                    Logging::err("[vga/text]: failed to get video type");
                    return;
            }
        }
        //vga_text_scroll_buffer = ushort_str(vga_text_width);
        static unsigned short buff[vga_text_width];
        vga_text_scroll_buffer = buff;
        X, Y = 0, 0;
        clean();
        init = true;
    }
    else if (size == 0)
        Logging::warn("[vga/text]: no text fb is allocated");
    else Logging::err("[vga/text]: invalid size");
}