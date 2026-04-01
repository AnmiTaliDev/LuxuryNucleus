add_library(helper_gpu OBJECT gpu.cpp)
add_library(helper_fb OBJECT fb.cpp)

target_link_libraries(NucleusKernel PRIVATE helper_gpu helper_fb)