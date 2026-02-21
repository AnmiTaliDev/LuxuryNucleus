add_library(driver_bda OBJECT bda.cpp)

target_precompile_headers(driver_bda PRIVATE ../../include/drivers/bda.hpp PRIVATE ../../include/mmio/bda.hpp)