/* 
VGA text framebuffer driver for legacy BIOS
*/

#include <drivers/bda.hpp>
#include <logging.hpp>
#include <mmio/alloc.hpp>
#include <library/strmgr/ports.hpp>
#include <library/strmgr/strings.hpp>
#include <drivers/graphics/gpu/fb/vga/text.hpp>
using namespace Drivers::Graphics::FB::VGA;
using namespace Library::strmgr;

#define vga_text_width  80
#define vga_text_height 25

#define mmio_addr_vga_text_fb_colour     0xB8000
#define mmio_addr_vga_text_fb_monochrome 0xB0000
#define mmio_addr_vga_graphics_fb        0xA0000

//volatile unsigned char *const vga_graphics_buffer = ;
volatile unsigned short *vga_text_buffer;
volatile unsigned short *vga_text_scroll_buffer;

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

void vga_text_fb::enable_cursor(const unsigned char &high_scanline, const unsigned char &low_scanline)
{
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | high_scanline);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | low_scanline);
}

void vga_text_fb::disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void vga_text_fb::clean()
{
    set_attr(LIGHT_GRAY, BLACK, 0);
    disable_cursor();
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
    Logging::info("[vga/text]: checking video type in BDA...");
    enum BDA::video_type videotype = BDA::video_type();
    if (videotype != BDA::VIDEO_TYPE_NONE)
    {
        switch (videotype)
        {
            case BDA::VIDEO_TYPE_COLOUR:
                Logging::info("[vga/text]: detected colour video type");
                vga_text_buffer = reinterpret_cast<volatile unsigned short*>(mmio_addr_vga_text_fb_colour);
                break;
            case BDA::VIDEO_TYPE_MONOCHROME:
                Logging::info("[vga/text]: detected monochrome video type");
                vga_text_buffer = reinterpret_cast<volatile unsigned short*>(mmio_addr_vga_text_fb_monochrome);
                break;
            default:
                Logging::err("[vga/text]: failed to get video type");
                return;
        }
    }
    Logging::info("[vga/text]: checking size...");
    if (Library::strmgr::size_of(reinterpret_cast<volatile void*>(vga_text_buffer)) == 32775)
    {
        vga_text_scroll_buffer = MMIO::ushort_str(vga_text_width);
        X = 0;
        Y = 0;
        clean();
        init = true;
    }
    else
        Logging::err("invalid size");
}