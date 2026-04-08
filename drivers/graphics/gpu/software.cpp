/*
The "software acceleration" GPU driver
*/

#include <logging.hpp>
#include <drivers/graphics/gpu/fb/vga/text.hpp>
#include <drivers/graphics/gpu/software.hpp>
using namespace Drivers::Graphics::GPU;
using namespace Drivers::Graphics::FB;

void (*draw_char_func)(const volatile char&) = nullptr;
void (*draw_pixel_func)(const volatile char&) = nullptr;
bool Software::inited = false;

void set_fb_helper(void (*char_func)(const volatile char&), void (*pixel_func)(const volatile char&))
{
    Logging::info("[gpu/software]: updating framebuffer helper...");
    if (*char_func == *pixel_func)
        Logging::warn("[gpu/software]: this FB supports only text characters!");
    draw_char_func = char_func; draw_pixel_func = pixel_func;
}

void FB_vga_text()
{
    Logging::info("[gpu/software]: checking VGA text FB...");
    if (VGA_text::init(); VGA_text::inited)
    {
        Logging::info("[gpu/software]: using VGA text as primary FB");
        set_fb_helper(VGA_text::put_char,VGA_text::put_char);
    }
}

void Software::draw_char(const volatile char &what)
{
    draw_char_func(what);
}

void Software::draw_pixel(const volatile char &what)
{
    draw_pixel_func(what);
}

void Software::init()
{
    if (!inited)
    {
        FB_vga_text();
        inited = draw_char_func != nullptr;

        if (!inited)
            Logging::warn("[gpu/software]: no framebuffer is active!");
    }
}