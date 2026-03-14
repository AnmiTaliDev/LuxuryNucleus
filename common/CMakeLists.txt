add_library(common_logging OBJECT logging.cpp)
add_library(common_fbcon OBJECT fbcon.cpp)
add_library(common_uname OBJECT universal_info.cpp)

target_precompile_headers(common_logging PRIVATE ../include/init/logging.hpp PRIVATE ../include/logging/con.hpp PRIVATE ../include/logging/log.hpp)
target_precompile_headers(common_fbcon PRIVATE ../include/init/fbcon.hpp)
target_precompile_headers(common_uname PRIVATE ../include/uname.hpp)