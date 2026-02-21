add_library(general_logging OBJECT logging.cpp)
add_library(general_fbcon OBJECT fbcon.cpp)

target_precompile_headers(general_logging PRIVATE ../include/init/logging.hpp PRIVATE ../include/logging/con.hpp PRIVATE ../include/logging/log.hpp)
target_precompile_headers(general_fbcon PRIVATE ../include/init/fbcon.hpp)