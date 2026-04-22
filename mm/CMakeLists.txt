add_library(mm_alloc OBJECT alloc.cpp)
target_link_libraries(LuxuryNucleus PRIVATE mm_alloc)
add_library(mm_port_io OBJECT io/port.cpp)
target_link_libraries(LuxuryNucleus PRIVATE mm_port_io)