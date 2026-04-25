#include "hooks/logging.hpp"
#include "hooks/fbcon.hpp"
void kernel_init_general() asm("kernel_init_general");
#include <arch/kernel_alloc.hpp>
#include <library/strings.hpp>
#include <debug/logging.hpp>
void kernel_init_general()
{
    // init
    Logging::init();
    fbcon::init();
    // misc
    Logging::info(Library::Strings::to_string(220,false));
    Logging::info("f");
    // end
}