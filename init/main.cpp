#include <logging.hpp>
#include <init/logging.hpp>
#include <init/fbcon.hpp>
extern unsigned long long nkernel_end;
void init_start() asm("init_start");

void init_start()
{
    Logging::init();
    Logging::info("Starting NucleusKernel...");
    fbcon::init();
}