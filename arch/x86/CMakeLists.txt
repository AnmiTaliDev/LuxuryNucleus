set(LINKER_SCRIPT "script.ld")
cmake_path(ABSOLUTE_PATH LINKER_SCRIPT)
target_link_options(LuxuryNucleus PRIVATE -T${LINKER_SCRIPT})
set_target_properties(LuxuryNucleus PROPERTIES LINK_DEPENDS "${LINKER_SCRIPT}")

if ( arch_bit_capacity STREQUAL "32" )
    add_subdirectory(ia-32)
else()
    add_subdirectory(amd64)
endif()

add_library(arch_multiboot2 OBJECT multiboot2.cpp)
target_link_libraries(LuxuryNucleus PRIVATE arch_multiboot2)

add_library(arch_pmio OBJECT pmio.cpp)
target_link_libraries(LuxuryNucleus PRIVATE arch_pmio)