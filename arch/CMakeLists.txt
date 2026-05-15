add_executable(LuxuryNucleus)
set_target_properties(LuxuryNucleus PROPERTIES OUTPUT_NAME "lnucleus" SUFFIX ".elf")

if(arch STREQUAL "x86")
    add_subdirectory(x86)
endif()