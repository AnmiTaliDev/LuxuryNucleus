#include <general/fbcon.hpp>
#include <general/logging.hpp>
#include <drivers/graphics/fb/vga.hpp>

void (*fbcon::fb_func)(const char&) = nullptr;

/*static void log(const char* text)
{
    char* t = "fbcon: " + text;
    Logging::info("fbcon: "+text);
}*/

void fbcon::update_fb_helper(void (*func)(const char&)){
    Logging::info("fbcon: updating framebuffer helper...");
    fb_func = func;
    Logging::write_char = Logging::_write_char__with_fbcon;
}

static bool fbcon_choose_fb()
{
    // VGA text framebuffer
    static VGA::vga_text_fb vga_fb;
    if (vga_fb.init)
    {
        VGA::helper::fb = &vga_fb;
        Logging::info("fbcon: using VGA text fb helper");
        fbcon::update_fb_helper(VGA::helper::fb_func);
        return VGA::helper::fb->init;
    }
    return false;
}

void fbcon::init()
{
    Logging::info("fbcon: initializing, choosing fb helper...");
    if (fbcon_choose_fb())
    {
        for (unsigned len = 0; len != Logging::buf_size; len++)
            fb_func(Logging::buffer[len]);
        Logging::info("---------------------------------");
        Logging::info("fbcon: exported logs buffer to fb");
    }
    else
    {
        Logging::info("fbcon: no showing fb was detected");
    }
}