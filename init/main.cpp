#include <arch/stack.hpp>
#include <init/logging.hpp>
#include <init/fbcon.hpp>
#include <logging/log.hpp>
#include <helpers/fb.hpp>
#include <library/strmgr.hpp>
void _start() asm("_start");

void _start()
{
    asm volatile
    (
        "movq %0, %%rsp"
        : 
        : "i"(&Arch::stack_top)
    );
    Logging::init();
    Logging::info("Starting PlumberCore...");
    Logging::warn(Library::strmgr::itos(10043434));
    fbcon::init();
    Logging::info("Starting PlumberCore...");
}