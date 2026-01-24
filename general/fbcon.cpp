#include <general/fbcon.hpp>
#include <general/logging.hpp>
#include <general/helpers/fb.hpp>

void (*fbcon::fb_func)(const char&) = nullptr;

/*static void log(const char* text)
{
    char* t = "fbcon: " + text;
    Logging::info("fbcon: "+text);
}*/

void fbcon::update_fb_helper(void (*func)(const char&)){
    Logging::info("[fbcon]: updating framebuffer helper...");
    fb_func = func;
    Logging::write_char = Logging::_write_char__with_fbcon;
}

static bool fbcon_choose_fb()
{
    // VGA text framebuffer
    if (Helpers::FB::VGA_text::init())
    {
        Logging::info("[fbcon]: setting VGA text as primary fb.");
        fbcon::update_fb_helper(Helpers::FB::VGA_text::print);
        return true;
    }
    return false;
}

void fbcon::init()
{
    Logging::info("[fbcon]: initializing, choosing fb helper...");
    if (fbcon_choose_fb())
    {
        for (unsigned len = 0; len != Logging::buf_size; len++)
            fb_func(Logging::buffer[len]);
        Logging::info("---------------------------------");
        Logging::info("[fbcon]: exported logs buffer to fb");
    }
    else
        Logging::info("[fbcon]: no active fb was detected");
}