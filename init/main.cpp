#include <init/logging.hpp>
#include <init/fbcon.hpp>
#include <logging/log.hpp>
#include <helpers/fb.hpp>
#include <library/strmgr.hpp>
void kernel_init_start() asm("kernel_init_start");

void kernel_init_start()
{
    Logging::init();
    Logging::info("Starting PlumberCore...");
    Logging::warn(Library::strmgr::itos(10043434));
    fbcon::init();
    Logging::info("Starting PlumberCore...");
}