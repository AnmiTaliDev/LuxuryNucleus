#include <arch/kernel_alloc.hpp>
#include "hooks/logging.hpp"
#include "hooks/fbcon.hpp"
#include "general.hpp"
#include <debug/logging.hpp>
#include <library/strings.hpp>

void Initialization::General()
{
    // init
    Logging::init();
    fbcon::init();
    // misc
    Logging::warn(Library::Strings::to_string(-12,true));
    // end
}