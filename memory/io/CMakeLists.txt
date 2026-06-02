add_library(memory_io_port OBJECT port.cpp)
target_link_libraries(lnucleus PRIVATE memory_io_port)