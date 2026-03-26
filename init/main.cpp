#include <logging.hpp>
#include <init/logging.hpp>
#include <init/fbcon.hpp>
#include <mmio/alloc.hpp>
#include <mmio/get_ptr.hpp>
#include <helpers/gpu.hpp>
void init_start() asm("init_start");

void init_start()
{
    Logging::init();
    Logging::info("Starting NucleusKernel...");
    Logging::warn("okak");
    fbcon::init();
    Logging::warn("okak");
    Helpers::GPU::SoftwareAccel::draw_char('f');
    
}