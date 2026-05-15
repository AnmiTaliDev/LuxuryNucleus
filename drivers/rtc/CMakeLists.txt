add_library(driver_cmos OBJECT cmos.cpp)
target_link_libraries(LuxuryNucleus PRIVATE driver_cmos)