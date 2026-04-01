add_library(library_strmgr OBJECT strmgr.cpp)

target_link_libraries(NucleusKernel PRIVATE library_strmgr)