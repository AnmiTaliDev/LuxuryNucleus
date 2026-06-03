/*
The "software acceleration" GPU driver
*/

#include <debug/logging.hpp>
#include "fb/vga.hpp"
#include "software.hpp"
using namespace Drivers::Graphics;

void (*volatile GPU::Software::draw_char)(const volatile char &) = nullptr;
void (*volatile GPU::Software::draw_pixel)(const volatile char &) = nullptr;
bool GPU::Software::inited = false;

static void set_fb_func(void (*const char_func)(const volatile char&), void (*const pixel_func)(const volatile char&))
{
    if (char_func == pixel_func)
        Debug::Logging::warn("[gpu/software]: this FB supports only text entries!");
    GPU::Software::draw_char = char_func;
    GPU::Software::draw_pixel = pixel_func;
}

static void FB_vga_text()
{
    Debug::Logging::info("[gpu/software]: checking VGA text FB...");
    if (FB::VGA_text::init(); FB::VGA_text::inited)
    {
        Debug::Logging::info("[gpu/software]: using VGA text as primary FB");
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
            Debug::Logging::warn("[gpu/software]: no framebuffer is active!");
    }
}