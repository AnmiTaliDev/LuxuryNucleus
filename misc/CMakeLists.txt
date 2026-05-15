add_library(misc_delay OBJECT delay.cpp)
target_link_libraries(LuxuryNucleus PRIVATE misc_delay)