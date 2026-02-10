#include <general/helpers/fb.hpp>
#include <general/logging/log.hpp>
#include <drivers/graphics/fb/vga.hpp>

VGA::vga_text_fb *VGA_text_instance = nullptr;

Helpers::FB::VGA_text::instance::instance()
{
    Logging::info("[helpers/vga]: initializing VGA text driver..");
    VGA::vga_text_fb vga_fb;
    VGA_text_instance = &vga_fb;
    init = &VGA_text_instance->init;
}

void Helpers::FB::VGA_text::print(const unsigned char &what)
{
    VGA_text_instance->put_char(what);
}