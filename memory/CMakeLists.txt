add_library(memory_alloc OBJECT alloc.cpp)
target_link_libraries(lnucleus PRIVATE memory_alloc)

add_subdirectory(io)

add_subdirectory(paging)