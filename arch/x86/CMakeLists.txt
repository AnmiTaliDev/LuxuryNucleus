add_library(arch_multiboot2 OBJECT multiboot2.cpp)
add_library(arch_stack OBJECT stack.S)

target_link_libraries(LuxuryNucleus PRIVATE arch_multiboot2 arch_stack)