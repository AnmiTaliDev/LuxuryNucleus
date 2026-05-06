add_library(misc_delay OBJECT delay.cpp)
target_link_libraries(lnucleus PRIVATE misc_delay)