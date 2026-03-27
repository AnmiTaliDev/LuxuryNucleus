#include <logging.hpp>
#include <init/logging.hpp>
#include <init/fbcon.hpp>
#include <mmio/alloc.hpp>
#include <mmio/get_ptr.hpp>
#include <helpers/fb.hpp>
extern unsigned long long nkernel_start, nkernel_end;
void init_start() asm("init_start");

void init_start()
{
    Logging::init();
    fbcon::init();
    Logging::err("FATAL: Nothing what to do.");
    Logging::info("gg");

    __asm__ volatile(
        "cli\n\t"
        "hlt\n\t"
    );
}