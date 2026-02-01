#include <general/helpers/fb.hpp>
#include <general/logging/log.hpp>
#include <drivers/graphics/fb/vga.hpp>

VGA::vga_text_fb *VGA_text_instance = nullptr;

bool Helpers::FB::VGA_text::init()
{
    Logging::info("[helpers/vga]: initializing VGA text driver..");
    static VGA::vga_text_fb vga_fb;
    VGA_text_instance = &vga_fb;
    return VGA_text_instance->init;
}

void Helpers::FB::VGA_text::print(const char &what)
{
    VGA_text_instance->put_char(what);
    //VGA_text_instance->sync();
}