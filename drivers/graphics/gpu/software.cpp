/*
The "software acceleration" GPU driver
*/

#include <logging.hpp>
#include <mmio/alloc.hpp>
#include <helpers/fb.hpp>
#include <helpers/gpu.hpp>
#include <drivers/graphics/gpu/software.hpp>
using namespace Drivers::Graphics::GPU;
using namespace Helpers::FB;

void (*draw_char_func)(const volatile char&) = nullptr;
void (*draw_pixel_func)(const volatile char&) = nullptr;

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
    VGA_text::instance Helper_FB_VGA_text = VGA_text::instance();
    if (Helper_FB_VGA_text.init)
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

Software::Software()
{
    FB_vga_text();
    init = draw_char_func != nullptr;

    if (!init)
        Logging::warn("[gpu/software]: no framebuffer is active!");
}