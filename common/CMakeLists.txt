add_library(common_logging OBJECT logging.cpp)
add_library(common_fbcon OBJECT fbcon.cpp)
add_subdirectory(mmio)

target_link_libraries(NucleusKernel PRIVATE common_logging common_fbcon)