add_library(arch_boot OBJECT boot.S)
target_link_libraries(lnucleus PRIVATE arch_boot)