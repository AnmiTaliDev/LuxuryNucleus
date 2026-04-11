#include <logging.hpp>
#include <arch/stack.hpp>
#include <init/logging.hpp>
#include <init/fbcon.hpp>
void _start() asm("_start");

void _start()
{
    asm
    (
        "mov esp, %0"
        : "=m" (Architecture::x86::stack_top)
        :
        : "memory"
    );
    // init
    Logging::init();
    fbcon::init();
    // misc
    Logging::warn("dd");
    // end
    asm
    (
        "cli\nhlt"
    );
}