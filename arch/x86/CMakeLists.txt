add_library(arch_boot OBJECT boot.s)
add_library(arch_multiboot2 OBJECT multiboot2.cpp)

#target_compile_options(arch_boot )
target_precompile_headers(arch_multiboot2 PRIVATE ../../include/arch/multiboot2.hpp)