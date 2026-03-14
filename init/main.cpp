#include <init/logging.hpp>
#include <init/fbcon.hpp>
#include <logging/log.hpp>
#include <helpers/fb.hpp>
#include <library/strmgr.hpp>
#include <uname.hpp>
void kernel_init_start() asm("kernel_init_start");

void kernel_init_start()
{
    Logging::init();
    fbcon::init();
    Logging::info(uname_kernel);
}