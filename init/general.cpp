#include <arch/alloc/init_services.hpp>
#include "services/logger.hpp"
#include "services/fbcon.hpp"
#include "general.hpp"

#include <debug/logging.hpp>
constexpr static volatile char __attribute__((section(".rodata.init_services"),used)) array[123] = {1,2,'x','y','i'};

void Initialization::General()
{
    // init
    Debug::Logging::init();
    Graphics::fbcon::init();
    // misc
    //Debug::Logging::info(mmio_addr_alloc_initservices_start);
    // end
}