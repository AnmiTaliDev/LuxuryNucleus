/* 
VGA text framebuffer driver for legacy BIOS
*/

#define mmio_addr_graphics_fb_vga_text (volatile unsigned short*)0xB8000
#include <drivers/graphics/fb/vga.hpp>
#include <drivers/bda.hpp>
#include <general/logging.hpp>

volatile unsigned short* const vga_text_buffer = mmio_addr_graphics_fb_vga_text;

// Static VGA text framebuffer info
constexpr unsigned vga_width  = 80; // shows 79
constexpr unsigned vga_height = 25; // shows 24

void VGA::vga_text_fb::newline()
{
    column = 0;
    row++;
}

void VGA::vga_text_fb::set_color(const enum vga_colors &foreground, const enum vga_colors &background)
{
    color_fg = foreground; color_bg = background;
    color = color_fg | color_bg << 4;
}

void VGA::vga_text_fb::put_entry_at(const unsigned short &entry, const unsigned &X, const unsigned &Y) 
{
	vga_text_buffer[Y * vga_width + X] = entry;
}

void VGA::vga_text_fb::clean()
{
    set_color(LIGHT_GRAY, BLACK);

    for (row = 0; row != vga_height; row++)
    { 
	    for (column = 0; column != vga_width; column++)
		    put_entry_at(0,column,row);
    }
    column = 0; row = 0;
}

void VGA::vga_text_fb::scroll()
{
    for (row = 0; row != vga_height; row++)
    {
        unsigned short row_buff[vga_width];
        for (column = 0; column != vga_width; column++)
            row_buff[column] = vga_text_buffer[row * vga_width + column];
        row--;
        for (column = 0; column != vga_width; column++)
            put_entry_at(row_buff[column],column,row);
        row++;
    }
    row = 24;
    for (column = 0; column != vga_width; column++)
        put_entry_at(0,column,row);
    column = 0;
}

void VGA::vga_text_fb::put_char(const unsigned char &what)
{
    switch (what)
    {
        case '\r': 
            column = 0;
            break;
        case '\n':
            newline();
            break;
        default:
            put_entry_at((unsigned short)(what | color << 8), column, row);
            if (column++ == vga_width)
                newline();
    }
	if (row == vga_height) scroll();
}

VGA::vga_text_fb::vga_text_fb()
{
    Logging::info("[Drivers/FB/VGA]: getting video type from bda...");
    enum video_type bda_video_type = BDA::get_video_type();
    if (bda_video_type != VIDEO_TYPE_NONE)
    {
        switch (bda_video_type)
        {
            case VIDEO_TYPE_COLOUR:
                Logging::info("[Drivers/FB/VGA]: detected colour video type");
                break;
            case VIDEO_TYPE_MONOCHROME:
                Logging::info("[Drivers/FB/VGA]: detected monochrome video type");
                break;
        }
        Logging::info("[Drivers/FB/VGA]: checking text mode fb size...");
        unsigned size = 0;
        while (vga_text_buffer[size])
            size++;
        if (size == 16388)
        {
            Logging::info("[Drivers/FB/VGA]: initializing fb...");
            clean();
            init = true;
        }
        else if (size == 0)
            Logging::warn("[Drivers/FB/VGA]: no text fb is allocated");
        else Logging::err("[Drivers/FB/VGA]: invalid size");
    }
}