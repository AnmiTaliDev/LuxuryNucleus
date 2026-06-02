add_library(memory_paging OBJECT paging.cpp)
target_link_libraries(lnucleus PRIVATE memory_paging)