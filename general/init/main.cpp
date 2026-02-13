#include <general/init/logging.hpp>
#include <general/init/fbcon.hpp>
#include <general/logging/log.hpp>
#include <general/helpers/fb.hpp>
void kernel_init_start() asm("kernel_init_start");

void kernel_init_start()
{
    Logging::init();
    Logging::info("Starting PlumberCore...");
    fbcon::init();
    Logging::info("Starting PlumberCore...");
}