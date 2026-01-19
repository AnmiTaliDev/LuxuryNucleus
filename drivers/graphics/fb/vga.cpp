/* 
VGA text framebuffer driver for legacy BIOS
*/

#include <drivers/graphics/fb/vga.hpp>
#include <drivers/bda.hpp>

void VGA::vga_text_fb::newline()
{
    column = 0;
    row++;
}

void VGA::vga_text_fb::set_color(enum vga_colors foreground, enum vga_colors background)
{
    color_fg = foreground; color_bg = background;
    color = color_fg | color_bg << 4;
}

void VGA::vga_text_fb::put_char_at(const unsigned short &what, const unsigned &X, const unsigned &Y) 
{
	vga_buffer[Y * vga_width + X] = what | color << 8;
}

void VGA::vga_text_fb::clean()
{
    column = 0;
    row = 0;
    set_color(LIGHT_GRAY, BLACK);

    for (unsigned y = 0; y != vga_height; y++)
    {
	    for (unsigned x = 0; x != vga_width; x++)
		    put_char_at('\0',x,y);
    }
}

void VGA::vga_text_fb::scroll()
{
    for (row = 0; row != vga_height; ++row)
    {
        unsigned short row_buff[vga_width];
        for (column = 0; column != vga_width; ++column)
            row_buff[column] = vga_buffer[row * vga_width + column];
        row--;
        for (column = 0; column != vga_width; ++column)
            put_char_at(row_buff[column],column,row);
        row++;
    }
    row = 24;
    for (column = 0; column != vga_width; ++column)
        put_char_at('\0',column,row);
    column = 0;
}

void VGA::vga_text_fb::put_char(const unsigned short &what)
{
    if (what == '\r') column = 0;
    else if (what == '\n')
        newline();
    else
    {
        put_char_at(what, column, row);
        column++;
        if (column == vga_width)
            newline();
    }
	if (row == vga_height) scroll();
}

VGA::vga_text_fb::vga_text_fb()
{
    enum video_type bda_video_type = BDA::get_video_type();
    if (bda_video_type != VIDEO_TYPE_NONE)
    {
        unsigned size = 0;
        while (vga_buffer[size])
            size++;
        if (size == 16388)
        {
            clean();
            init = true;
        }
    }
}

VGA::vga_text_fb *VGA::helper::fb = nullptr;
void VGA::helper::fb_func(const char &data)
{
    fb->put_char(data);
}