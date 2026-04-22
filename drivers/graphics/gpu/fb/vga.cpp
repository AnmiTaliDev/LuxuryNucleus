/* 
VGA text framebuffer driver for legacy BIOS
*/

#include <drivers/misc/bda.hpp>
#include <debug/logging.hpp>
#include <mm/io/port.hpp>
#include <mm/alloc.hpp>
#include <library/strings.hpp>
#include <library/libfb.hpp>
#include <misc/vga_colors.hpp>
#include "vga.hpp"
using namespace MM::IO;
using namespace Drivers::Graphics::FB;
using namespace Miscellaneous::FB::VGA;
using namespace Library;

const volatile unsigned short pmio_addr_vga_register_port_1 = 0x3D4;
const volatile unsigned short pmio_addr_vga_register_port_2 = 0x3D5;
#define mmio_addr_vga_text_fb_colour     0xB8000
#define mmio_addr_vga_text_fb_monochrome 0xB0000
#define mmio_addr_vga_graphics_fb        0xA0000
const volatile unsigned vga_text_height = 25;
const volatile unsigned vga_text_width = 80;

//volatile unsigned char *const vga_graphics_buffer = ;
volatile unsigned short *vga_text_buffer;
volatile unsigned short *vga_text_scroll_buffer;
Library::FB *vga_text_libfb;
volatile unsigned short attribute;

bool VGA_text::inited = false;

void put_entry(const unsigned short entry) 
{
	vga_text_buffer[vga_text_libfb->TwoD()] = entry | attribute;
}

void fill_with_zeros()
{
    for (vga_text_libfb->column = 0; vga_text_libfb->column != vga_text_width; vga_text_libfb->column++)
	    put_entry(0);
    vga_text_libfb->column = 0;
}

void set_attr(const enum vga_colors &foreground, const enum vga_colors &background, const bool &blink)
{
    attribute = (foreground | background << 4 | blink << 7) << 8;
}

void enable_cursor(const unsigned char &high_scanline, const unsigned char &low_scanline)
{
    Ports::write(pmio_addr_vga_register_port_1, 0x0A);
	Ports::write(pmio_addr_vga_register_port_2, (Ports::read(pmio_addr_vga_register_port_2) & 0xC0) | high_scanline);

	Ports::write(pmio_addr_vga_register_port_1, 0x0B);
	Ports::write(pmio_addr_vga_register_port_2, (Ports::read(pmio_addr_vga_register_port_2) & 0xE0) | low_scanline);
}

void disable_cursor()
{
	Ports::write(pmio_addr_vga_register_port_1, 0x0A);
	Ports::write(pmio_addr_vga_register_port_2, 0x20);
}

void clean()
{
    set_attr(LIGHT_GRAY, BLACK, 0);
    disable_cursor();
    for (vga_text_libfb->row = 0; vga_text_libfb->row != vga_text_libfb->height; vga_text_libfb->row++)
        fill_with_zeros();
    vga_text_libfb->row = 0;
}

void scroll()
{
    for (vga_text_libfb->row = 0; vga_text_libfb->row != vga_text_libfb->height; vga_text_libfb->row++)
    {
        volatile unsigned row = vga_text_libfb->TwoD_row();
        for (vga_text_libfb->column = 0; vga_text_libfb->column != vga_text_width; vga_text_libfb->column++)
            vga_text_scroll_buffer[vga_text_libfb->column] = vga_text_buffer[vga_text_libfb->TwoD_plus_column(row)];
        vga_text_libfb->row--;
        for (vga_text_libfb->column = 0; vga_text_libfb->column != vga_text_width; vga_text_libfb->column++)
            put_entry(vga_text_scroll_buffer[vga_text_libfb->column]);
        vga_text_libfb->row++;
    }
    vga_text_libfb->row = 24;
    fill_with_zeros();
}

void VGA_text::put_char(const volatile char &what)
{
    switch (what)
    {
        case '\r': 
            vga_text_libfb->column = 0;
            break;
        case '\n':
            vga_text_libfb->column = 0;
            vga_text_libfb->row++;
            break;
        case '\t':
            vga_text_libfb->column++;
            break;
        default:
            put_entry(what);
            vga_text_libfb->next_column();
            break;
    }
	if (vga_text_libfb->row == vga_text_libfb->height) scroll();
}

void VGA_text::init()
{
    if (!inited)
    {
        Logging::info("[vga/text]: checking video type in BDA...");
        enum BDA::vga_display_type type = BDA::get_vga_display_type();
        switch (type)
        {
            case BDA::vga_display_type::COLOUR:
                Logging::info("[vga/text]: detected colour video type");
                vga_text_buffer = reinterpret_cast<volatile unsigned short*>(mmio_addr_vga_text_fb_colour);
                break;
            case BDA::vga_display_type::MONOCHROME:
                Logging::info("[vga/text]: detected monochrome video type");
                vga_text_buffer = reinterpret_cast<volatile unsigned short*>(mmio_addr_vga_text_fb_monochrome);
                break;
            case BDA::vga_display_type::NONE:
                Logging::warn("[vga/text]: video display is not present.");
                return;
            default:
                Logging::err("[vga/text]: failed to get video type");
                return;
        }
        Logging::info("[vga/text]: checking size...");
        if (Library::Strings::length_of(vga_text_buffer) == 32775)
        {
            vga_text_scroll_buffer = reinterpret_cast<volatile unsigned short*>(MM::alloc(vga_text_width));
            *vga_text_libfb = Library::FB(vga_text_width,vga_text_height);
            clean();
            inited = true;
        }
        else
            Logging::err("invalid size");
    }
}