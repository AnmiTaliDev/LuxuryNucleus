add_library(driver_bda OBJECT bda.cpp)

target_link_libraries(NucleusKernel PRIVATE driver_bda)