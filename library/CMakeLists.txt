add_library(library_strmgr OBJECT strmgr.cpp)
add_library(library_libfb OBJECT libfb.cpp)

target_precompile_headers(library_strmgr PRIVATE ../include/library/strmgr.hpp)
target_precompile_headers(library_libfb PRIVATE ../include/library/libfb.hpp)