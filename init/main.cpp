#include <arch/alloc/init_services.hpp>
#include "services/logger.hpp"
#include "services/fbcon.hpp"
#include "main.hpp"

bool not_crashed = true;

void Initialization::General()
{
    Debug::Logging::init();
    Graphics::fbcon::init();
    while (not_crashed)
    {
        //...
    }
}