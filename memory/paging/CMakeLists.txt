add_library(memory_paging OBJECT control.S)
target_link_libraries(lnucleus PRIVATE memory_paging)