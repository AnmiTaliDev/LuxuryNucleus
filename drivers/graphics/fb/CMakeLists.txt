add_library(driver_fb_vga OBJECT vga.cpp)

target_precompile_headers(driver_fb_vga PRIVATE ../../../include/drivers/graphics/fb/vga.hpp PRIVATE ../../../include/mmio/vga.hpp)