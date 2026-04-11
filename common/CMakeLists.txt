add_library(common_init OBJECT init.cpp)
add_library(common_mmio OBJECT mmio.cpp)
add_library(common_logging OBJECT logging.cpp)
add_library(common_fbcon OBJECT fbcon.cpp)

target_link_libraries(LuxuryNucleus PRIVATE common_init common_mmio common_logging common_fbcon)