#include <logging.hpp>
#include <mmio/alloc.hpp>
#include <drivers/graphics/gpu/software.hpp>
#include <helpers/gpu.hpp>
using namespace Drivers::Graphics::GPU;
using namespace Helpers::GPU;

Software *GPU_software_ptr = nullptr;
SoftwareAccel::instance::instance()
{
    Logging::info("[helpers/gpu]: initializing CPU-based render driver...");
    GPU_software_ptr = reinterpret_cast<Software*>(*alloc_safe(sizeof(Software*)));
    *GPU_software_ptr = Software();
    init = GPU_software_ptr->init;
}

void SoftwareAccel::draw_char(const char &what)
{
    GPU_software_ptr->draw_char(what);
}