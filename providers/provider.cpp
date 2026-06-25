#include <debug/logging.hpp>
#include "graphics/provide.hpp"
using namespace Providers;

extern const Graphics::GPU_provider_info *const providers_graphics_start[],
                                         *const providers_graphics_end[];

void (*Graphics::provide())(const char &)
{
    const Graphics::GPU_provider_info *ptr;
    for (ptr = *providers_graphics_start;
         ptr < *providers_graphics_end; ++ptr)
    {
        if (ptr)
        {
            if (ptr->init_func(); ptr->inited)
                break;
        }
    }
    return ptr->func;
}