#include <logging.hpp>
#include <drivers/graphics/gpu/fb/vga.hpp>
#include <helpers/fb.hpp>
using namespace Drivers::Graphics::FB;
using namespace Helpers::FB;

VGA::vga_text_fb *VGA_text_instance = nullptr;
VGA_text::instance::instance()
{
    Logging::info("[helpers/fb]: initializing VGA text driver..");
    static VGA::vga_text_fb vga_fb;
    VGA_text_instance = &vga_fb;
    init = &VGA_text_instance->init;
}

void VGA_text::put_char(const char &what)
{
    VGA_text_instance->put_char(what);
}