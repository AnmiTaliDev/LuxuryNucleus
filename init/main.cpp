#include <logging.hpp>
#include <init/logging.hpp>
#include <init/fbcon.hpp>
void _start() __asm__("_start");

void _start()
{
    __asm__ volatile
    (
        "mov stack_top, esp"
    );
    // init
    Logging::init();
    fbcon::init();
    // misc
    // end
    __asm__ volatile
    (
        "cli\nhlt"
    );
}