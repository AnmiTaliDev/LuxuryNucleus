add_library(driver_cmos OBJECT cmos.cpp)
target_link_libraries(lnucleus PRIVATE driver_cmos)