add_library(arch_boot OBJECT boot.S)
target_link_libraries(LuxuryNucleus PRIVATE arch_boot)