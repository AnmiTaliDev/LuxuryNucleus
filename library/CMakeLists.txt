add_library(library_libfb OBJECT libfb.cpp)
add_library(library_strings OBJECT strings.cpp)

target_link_libraries(LuxuryNucleus PRIVATE library_libfb library_strings)