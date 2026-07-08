#include <debug/logging.hpp>
#include "graphics/provide.hpp"
using namespace Providers;

extern Graphics::GPU_provider_info providers_graphics_start[] asm("providers_graphics_start"),
                                   providers_graphics_end[] asm("providers_graphics_end");

Graphics::GPU_provider_info *Providers::provide_gpu()
{
    static Graphics::GPU_provider_info *ptr = nullptr;
    for (ptr = providers_graphics_start;
         ptr < providers_graphics_end; ptr++)
    {
        (*ptr->init_func)();
        break;
    }
    return ptr;
}