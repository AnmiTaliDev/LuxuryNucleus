add_executable(LuxuryNucleus)
set_target_properties(LuxuryNucleus PROPERTIES OUTPUT_NAME "lnucleus" SUFFIX ".elf")
target_link_options(LuxuryNucleus PRIVATE -Wl,--whole-archive $<TARGET_FILE:lnucleus> -Wl,--no-whole-archive)
target_link_libraries(LuxuryNucleus PRIVATE lnucleus)

if(arch STREQUAL "x86")
    add_subdirectory(x86)
endif()