add_library(memory_alloc OBJECT alloc.cpp)
target_link_libraries(LuxuryNucleus PRIVATE memory_alloc)

add_subdirectory(io)