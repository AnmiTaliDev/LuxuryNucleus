#include <arch/alloc/init_services.hpp>
#include "services/logger.hpp"
#include "services/fbcon.hpp"
#include "general.hpp"

#include <debug/logging.hpp>

void Initialization::General()
{
    // init
    Debug::Logging::init();
    Graphics::fbcon::init();
    // misc
    // end
}