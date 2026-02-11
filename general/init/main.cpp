#include <general/init/logging.hpp>
#include <general/init/fbcon.hpp>
#include <general/logging/log.hpp>
#include <general/fbcon.hpp>
void kernel_init_start() asm("kernel_init_start");

void kernel_init_start()
{
    Logging::buffer_instance __Logging;
    Logging::__buffer_instance = &__Logging;
    Logging::info("Starting PlumberCore...");
    fbcon::init();
    Logging::info("vsdvfdfd");
}