add_library(init_general OBJECT general.cpp)
target_link_libraries(lnucleus PRIVATE init_general)

add_subdirectory(services)