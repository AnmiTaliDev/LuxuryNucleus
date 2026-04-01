add_library(arch_bootstrap OBJECT bootstrap.s)
add_library(arch_multiboot2 OBJECT multiboot2.s)

target_link_libraries(NucleusKernel PRIVATE arch_bootstrap arch_multiboot2)