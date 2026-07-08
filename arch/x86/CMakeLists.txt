set(LINKER_SCRIPT "script.ld")
cmake_path(ABSOLUTE_PATH LINKER_SCRIPT)
target_link_options(lnucleus PRIVATE -T${LINKER_SCRIPT})
set_target_properties(lnucleus PROPERTIES LINK_DEPENDS "${LINKER_SCRIPT}")

add_library(arch_boot OBJECT boot.S cpuid.S)
target_link_libraries(lnucleus PRIVATE arch_boot)

add_library(arch_multiboot2 OBJECT multiboot2.cpp)
target_link_libraries(lnucleus PRIVATE arch_multiboot2)

add_library(arch_pmio OBJECT pmio.cpp)
target_link_libraries(lnucleus PRIVATE arch_pmio)