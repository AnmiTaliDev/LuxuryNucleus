#include "info.hpp"

#define GPU_provider_import(NAME,PRINT_FUNC,INIT_FUNC,INIT_VAR) \
Providers::Graphics::GPU_provider_info _GPU_INFO_CARD__ ## NAME \
__attribute__((section(".providers_graphics"))) \
{ \
    .name = #NAME, \
    .inited = INIT_VAR, \
    .func = PRINT_FUNC, \
    .init_func = INIT_FUNC \
};
