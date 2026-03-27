#include <logging.hpp>
#include <drivers/graphics/gpu/software.hpp>
#include <helpers/gpu.hpp>
using namespace Drivers::Graphics::GPU;
using namespace Helpers::GPU;

static Software *GPU_software_instance = nullptr;
SoftwareAccel::instance::instance()
{
    Logging::info("[helpers/gpu]: initializing CPU-based render driver...");
    static Software gpu_software;
    GPU_software_instance = &gpu_software;
    init = GPU_software_instance->init;
}

void SoftwareAccel::draw_char(const char &what)
{
    GPU_software_instance->draw_char(what);
}