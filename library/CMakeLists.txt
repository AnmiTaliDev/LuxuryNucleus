add_library(library_libfb OBJECT libfb.cpp)
target_link_libraries(lnucleus PRIVATE library_libfb)

add_library(library_strings OBJECT strings.cpp)
target_link_libraries(lnucleus PRIVATE library_strings)

add_library(library_integers OBJECT integers.cpp)
target_link_libraries(lnucleus PRIVATE library_integers)