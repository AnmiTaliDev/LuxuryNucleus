#include <general/init/fbcon.hpp>
#include <general/fbcon.hpp>
#include <general/logging/con.hpp>
#include <general/logging/log.hpp>
#include <general/helpers/fb.hpp>

//constexpr char log_prefix[10] = "[fbcon]: ";
void (*fbcon::fb_func)(const unsigned char&) = nullptr;

static void update_fb_helper(void (*func)(const unsigned char&)){
    Logging::info("[fbcon]: updating framebuffer helper...");
    fbcon::fb_func = func;
}

static bool fbcon_choose_fb()
{
    // VGA text framebuffer
    Helpers::FB::VGA_text::instance vga_text;
    if (vga_text.init)
    {
        Logging::info("[fbcon]: setting VGA text as primary fb.");
        update_fb_helper(Helpers::FB::VGA_text::print);
        return true;
    }
    return false;
}

void fbcon::init()
{
    Logging::info("[fbcon]: initializing, choosing fb helper...");
    if (fbcon_choose_fb())
    {
        Logging::switch_write_char_func();
        unsigned char __char;
        while (true)
        {
            __char = Logging::give_char_loop();
            if (__char)
            {
                fb_func(__char);
            } else break;
        }
        Logging::info("------------------------------------");
        Logging::info("[fbcon]: exported logs buffer to fb!");
    }
    else
        Logging::info("[fbcon]: no active fb was detected");
}