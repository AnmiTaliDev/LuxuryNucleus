#include <arch/kernel_alloc.hpp>
#include "hooks/logging.hpp"
#include "hooks/fbcon.hpp"
#include "general.hpp"

void Initialization::General()
{
    // init
    Logging::init();
    fbcon::init();
    // misc
    // end
}