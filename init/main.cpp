#include <logging.hpp>
#include <init/logging.hpp>
#include <init/fbcon.hpp>
#include <mmio/alloc.hpp>
#include <mmio/get_ptr.hpp>
#include <helpers/fb.hpp>
void init_start() asm("init_start");

void init_start()
{
    Logging::init();
    Logging::info("Starting NucleusKernel...");
    Logging::warn("sex");
    fbcon::init();
    Logging::warn("sex");
    

    Logging::err("FATAL ERR: Nothing what to do.");
    __asm__ volatile(
        "cli\n\t"
        "hlt\n\t"
    );
}