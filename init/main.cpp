#include <logging.hpp>
#include <mmio/alloc.hpp>
#include <library/strmgr/strings.hpp>
#include <init/logging.hpp>
#include <init/fbcon.hpp>
void init_start() asm("init_start");

void init_start()
{
    // init
    Logging::init();
    fbcon::init();
    // misc
    // end
}