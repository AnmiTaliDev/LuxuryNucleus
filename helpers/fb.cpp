#include <logging.hpp>
#include <mmio/alloc.hpp>
#include <drivers/graphics/gpu/fb/vga.hpp>
#include <helpers/fb.hpp>
using namespace Drivers::Graphics::FB;
using namespace Helpers::FB;

VGA::vga_text_fb *VGA_text_FB_ptr = nullptr;
VGA_text::instance::instance()
{
    Logging::info("[helpers/fb]: initializing VGA text driver..");
    VGA_text_FB_ptr = reinterpret_cast<VGA::vga_text_fb*>(*alloc_safe(sizeof(VGA::vga_text_fb*)));
    *VGA_text_FB_ptr = VGA::vga_text_fb();
    init = VGA_text_FB_ptr->init;
}

void VGA_text::put_char(const char &what)
{
    VGA_text_FB_ptr->put_char(what);
}