/*
The "software acceleration" GPU driver
*/

#include <logging.hpp>
#include <helpers/fb.hpp>
#include <helpers/gpu.hpp>
#include <drivers/graphics/gpu/software.hpp>
using namespace Drivers::Graphics::GPU;
using namespace Helpers::FB;

void (*draw_func)(const char&) = nullptr;

static void set_fb_helper(void (*func)(const char&))
{
    Logging::info("[gpu/software]: updating framebuffer helper...");
    draw_func = func;
}

static bool FB_vga_text()
{
    bool __return = false;
    Logging::info("[gpu/software]: checking VGA text FB...");
    static VGA_text::instance FB_vga_text_instance;
    if (FB_vga_text_instance.init)
    {
        Logging::info("[gpu/software]: using VGA text as primary FB");
        set_fb_helper(VGA_text::put_char);
        __return = true;
    }
    return __return;
}

void Software::draw_char(const char &what)
{
    draw_func(what);
}

Software::Software()
{
    init = FB_vga_text();

    if (!init)
        Logging::warn("[gpu/software]: no framebuffer is active!");
}