#include "hooks/logging.hpp"
#include "hooks/fbcon.hpp"
void kernel_init_general() asm("kernel_init_general");

void kernel_init_general()
{
    // init
    Logging::init();
    fbcon::init();
    // misc
    // end
}