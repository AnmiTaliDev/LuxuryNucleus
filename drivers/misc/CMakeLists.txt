add_library(driver_bda OBJECT bda.cpp)

target_link_libraries(LuxuryNucleus PRIVATE driver_bda)