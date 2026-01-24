#include <general/init/main.hpp>

void kernel_init_start()
{
    Logging::init();
    Logging::info("Starting PlumberCore...");
    fbcon::init();
}