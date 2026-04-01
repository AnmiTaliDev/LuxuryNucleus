#include <logging.hpp>
#include <drivers/graphics/gpu/software.hpp>
#include <helpers/gpu.hpp>
using namespace Drivers::Graphics::GPU;
using namespace Helpers::GPU;

Software *GPU_software_ptr = nullptr;
SoftwareAccel::instance::instance()
{
    Logging::info("[helpers/gpu]: initializing CPU-based render driver...");
    *GPU_software_ptr = Software();
    init = GPU_software_ptr->init;
}

void SoftwareAccel::draw_char(const volatile char &what)
{
    GPU_software_ptr->draw_char(what);
}

void SoftwareAccel::draw_pixel(const volatile char &what)
{
    GPU_software_ptr->draw_pixel(what);
}