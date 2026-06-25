#include "info.hpp"

#define GPU_provider_import(NAME,PRINT_FUNC,INIT_FUNC,INIT_VAR) \
static constexpr Providers::Graphics::GPU_provider_info \
_GPU_INFO_CARD__ ## NAME { .name = #NAME, .inited = INIT_VAR, .func = PRINT_FUNC, .init_func = INIT_FUNC}; \
static constexpr const Providers::Graphics::GPU_provider_info __attribute__((section(".providers_graphics"),used)) \
*const _GPU_PROVIDE__ ## NAME = &_GPU_INFO_CARD__ ## NAME;
