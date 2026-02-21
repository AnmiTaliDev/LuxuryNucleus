add_library(helper_fb OBJECT fb.cpp)

target_precompile_headers(helper_fb PRIVATE ../include/helpers/fb.hpp)