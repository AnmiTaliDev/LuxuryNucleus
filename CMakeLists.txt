cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)
project(NucleusKernel CXX ASM)

# Options
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/arch/x86/script.ld")
add_compile_options(-Wall -Wextra -O0 -ffreestanding -funsigned-char -fpermissive
                    -fno-signed-char -fno-rtti -fno-exceptions -fno-threadsafe-statics
                    -m32 -fno-PIE -fno-PIC -mno-red-zone -nostdlib)
add_link_options(-T${LINKER_SCRIPT} -nostdlib -no-pie -O0 -s -m32)
include_directories("${CMAKE_SOURCE_DIR}/include")

# Deps
add_subdirectory(arch)
add_subdirectory(library)
add_subdirectory(drivers)
add_subdirectory(init)
add_subdirectory(common)
add_subdirectory(helpers)

# Kernel
set_target_properties(NucleusKernel PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT} RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_link_libraries(NucleusKernel PRIVATE arch_bootstrap arch_multiboot2
                                  library_strmgr
                                  driver_gpu_software driver_bda driver_fb_vga
                                  helper_gpu helper_fb
                                  common_mmio_get_ptr common_mmio_alloc common_logging common_fbcon)
