add_library(arch_stack OBJECT stack.cpp)
add_library(arch_multiboot2 OBJECT multiboot2.cpp)

target_precompile_headers(arch_stack PRIVATE ../../include/arch/stack.hpp)
target_precompile_headers(arch_multiboot2 PRIVATE ../../include/arch/multiboot2.hpp)