/* 
VGA text framebuffer driver for legacy BIOS
*/

#include <drivers/bios/bda.hpp>
#include <debug/logging.hpp>
#include <memory/io/port.hpp>
#include <memory/alloc.hpp>
#include <providers/graphics/import.hpp>
#include <library/str_int.hpp>
#include <library/libfb.hpp>
#include "vga_colors.hpp"
#include "vga.hpp"
using namespace Drivers::Graphics::GPU::Software;
using namespace Miscellaneous::Graphics::GPU::VGA;
using namespace Memory::IO;
using namespace Library;

const unsigned short pmio_addr_vga_register_port_1 = 0x3D4;
const unsigned short pmio_addr_vga_register_port_2 = 0x3D5;
#define mmio_addr_vga_text_fb_colour     0xB8000
#define mmio_addr_vga_text_fb_monochrome 0xB0000
#define mmio_addr_vga_graphics_fb        0xA0000

bool VGA_text::inited = false;
Library::FB *vga_text_libfb;
// char *const vga_graphics_buffer = ;
unsigned short *vga_text_buffer,
               *vga_text_scroll_buffer,
               attribute;

static void put_entry(const unsigned short entry) 
{
	vga_text_buffer[vga_text_libfb->TwoD()] = entry | attribute;
}

static void fill_with_zeros()
{
    for (vga_text_libfb->column = 0; vga_text_libfb->column != vga_text_libfb->width; vga_text_libfb->column++)
	    put_entry(0);
    vga_text_libfb->column = 0;
}

static void set_attr(const enum vga_colors &foreground, const enum vga_colors &background, const bool &blink)
{
    attribute = (foreground | background << 4 | blink << 7) << 8;
}

static void enable_cursor(const char &high_scanline, const char &low_scanline)
{
    Ports::write(pmio_addr_vga_register_port_1, 0x0A);
	Ports::write(pmio_addr_vga_register_port_2, (Ports::read(pmio_addr_vga_register_port_2) & 0xC0) | high_scanline);

	Ports::write(pmio_addr_vga_register_port_1, 0x0B);
	Ports::write(pmio_addr_vga_register_port_2, (Ports::read(pmio_addr_vga_register_port_2) & 0xE0) | low_scanline);
}

static void disable_cursor()
{
	Ports::write(pmio_addr_vga_register_port_1, 0x0A);
	Ports::write(pmio_addr_vga_register_port_2, 0x20);
}

static void clean()
{
    set_attr(LIGHT_GRAY, BLACK, 0);
    disable_cursor();
    for (vga_text_libfb->row = 0; vga_text_libfb->row != vga_text_libfb->height; vga_text_libfb->row++)
        fill_with_zeros();
    vga_text_libfb->row = 0;
}

static void scroll()
{
    for (vga_text_libfb->row = 0; vga_text_libfb->row != vga_text_libfb->height; vga_text_libfb->row++)
    {
        unsigned row = vga_text_libfb->TwoD_row();
        for (vga_text_libfb->column = 0; vga_text_libfb->column != vga_text_libfb->width; vga_text_libfb->column++)
            vga_text_scroll_buffer[vga_text_libfb->column] = vga_text_buffer[vga_text_libfb->TwoD_plus_column(row)];
        vga_text_libfb->row--;

        for (vga_text_libfb->column = 0; vga_text_libfb->column != vga_text_libfb->width; vga_text_libfb->column++)
            put_entry(vga_text_scroll_buffer[vga_text_libfb->column]);
        vga_text_libfb->row++;
    }
    vga_text_libfb->row = 24;
    fill_with_zeros();
}

void VGA_text::put_char(const char &what)
{
    switch (what)
    {
        case '\r': 
            vga_text_libfb->column = 0;
            break;
        case '\n':
            vga_text_libfb->newline();
            break;
        default:
            if (vga_text_libfb->newline_at_end)
            {
                scroll();
                vga_text_libfb->newline_at_end = false;
            }
            put_entry(what);
            vga_text_libfb->next_column();
            break;
    }
	if (vga_text_libfb->row == vga_text_libfb->height) vga_text_libfb->newline_at_end = true;
}

void VGA_text::init()
{
    if (!inited)
    {
        Debug::Logging::info("[vga/text]: checking video type in BDA...");
        enum BDA::vga_display_type type = BDA::get_vga_display_type();
        switch (type)
        {
            case BDA::vga_display_type::COLOUR:
                Debug::Logging::info("[vga/text]: detected colour video type");
                vga_text_buffer = reinterpret_cast<unsigned short *>(mmio_addr_vga_text_fb_colour);
                break;
            case BDA::vga_display_type::MONOCHROME:
                Debug::Logging::info("[vga/text]: detected monochrome video type");
                vga_text_buffer = reinterpret_cast<unsigned short *>(mmio_addr_vga_text_fb_monochrome);
                break;
            case BDA::vga_display_type::NONE:
                Debug::Logging::warn("[vga/text]: video display is not present.");
                return;
            default:
                Debug::Logging::err("[vga/text]: failed to get video type");
                return;
        }
        vga_text_scroll_buffer = Memory::allocate<unsigned short>(80);
        static Library::FB vga_text_libfb_instance{80,25};
        vga_text_libfb = &vga_text_libfb_instance;
        clean();
        inited = true;
    }
}

GPU_provider_import(VGA,VGA_text::put_char,VGA_text::init,&VGA_text::inited)