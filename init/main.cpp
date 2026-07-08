#include "services/logger.hpp"
#include "services/fbcon.hpp"
#include "main.hpp"

static bool not_crashed = true;

void Initialization::General()
{
    Debug::Logging::init();
    Graphics::fbcon::init();
    while (not_crashed)
    {
        //...
    }
}