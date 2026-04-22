/*
The "software acceleration" GPU driver
*/

#include <debug/logging.hpp>
#include "fb/vga.hpp"
#include "software.hpp"
using namespace Drivers::Graphics;

void (*GPU::Software::draw_char)(const volatile char &) = nullptr;
void (*GPU::Software::draw_pixel)(const volatile char &) = nullptr;
bool GPU::Software::inited = false;

void set_fb_func(void (*const char_func)(const volatile char&), void (*const pixel_func)(const volatile char&))
{
    Logging::info("[gpu/software]: updating framebuffer helper...");
    if (char_func == pixel_func)
        Logging::warn("[gpu/software]: this FB supports only text characters!");
    GPU::Software::draw_char = char_func;
    GPU::Software::draw_pixel = pixel_func;
}

void FB_vga_text()
{
    Logging::info("[gpu/software]: checking VGA text FB...");
    if (FB::VGA_text::init(); FB::VGA_text::inited)
    {
        Logging::info("[gpu/software]: using VGA text as primary FB");
        set_fb_func(FB::VGA_text::put_char,FB::VGA_text::put_char);
    }
}

void GPU::Software::init()
{
    if (!inited)
    {
        FB_vga_text();
        inited = draw_char != nullptr || draw_pixel != nullptr;

        if (!inited)
            Logging::warn("[gpu/software]: no framebuffer is active!");
    }
}