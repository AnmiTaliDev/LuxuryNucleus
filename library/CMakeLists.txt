add_library(library_libfb OBJECT libfb.cpp)
target_link_libraries(lnucleus PRIVATE library_libfb)

add_library(library_str_int OBJECT str_int.cpp)
target_link_libraries(lnucleus PRIVATE library_str_int)