/*
The "software acceleration" GPU driver
*/

#include <logging.hpp>
#include <helpers/fb.hpp>
#include <helpers/gpu.hpp>
#include <drivers/graphics/gpu/software.hpp>
using namespace Drivers::Graphics::GPU;
using namespace Helpers::FB;

void Software::set_fb_helper(void (*func)(const char&))
{
    Logging::info("[gpu/software]: updating framebuffer helper...");
    draw_char = func;
}

bool Software::FB_vga_text()
{
    Logging::info("[gpu/software]: checking VGA text FB...");
    static VGA_text::instance FB_vga_text_instance;
    if (FB_vga_text_instance.init)
    {
        Logging::info("[gpu/software]: using VGA text as primary FB");
        set_fb_helper(VGA_text::put_char);
    }
    return FB_vga_text_instance.init;
}

Software::Software()
{
    init = FB_vga_text();

    if (!init)
        Logging::warn("[gpu/software]: no framebuffer is active!");
}