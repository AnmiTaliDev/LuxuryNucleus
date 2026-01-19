#include <general/logging.hpp>
#include <general/fbcon.hpp>
#include <drivers/graphics/fb/vga.hpp>
void kernel_init_start() asm("kernel_init_start");

void kernel_init_start()
{
    Logging::init();
    Logging::info("Starting PlumberCore...");
    fbcon::init();
}