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

void (*draw_func)(const char&) = nullptr;

void set_fb_helper(void (*func)(const char&))
{
    Logging::info("[gpu/software]: updating framebuffer helper...");
    draw_func = func;
}

void FB_vga_text()
{
    Logging::info("[gpu/software]: checking VGA text FB...");
    VGA_text::instance *Helper_FB_VGA_text_instance = reinterpret_cast<VGA_text::instance*>(*alloc_safe(sizeof(VGA_text::instance*)));
    *Helper_FB_VGA_text_instance = VGA_text::instance();
    if (Helper_FB_VGA_text_instance->init)
    {
        Logging::info("[gpu/software]: using VGA text as primary FB");
        set_fb_helper(VGA_text::put_char);
    }
}

void Software::draw_char(const char &what)
{
    draw_func(what);
}

Software::Software()
{
    FB_vga_text();
    init = draw_func != nullptr;

    if (!init)
        Logging::warn("[gpu/software]: no framebuffer is active!");
}