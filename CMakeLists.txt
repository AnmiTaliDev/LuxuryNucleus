cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
project(PlumberCore CXX ASM)

# Options
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/arch/x86/script.ld")
add_compile_options(-Wall -Wextra -O0 -ffreestanding -funsigned-char -fpermissive
                    -fno-signed-char -fno-common -fno-rtti -fno-exceptions -fno-threadsafe-statics
                    -mcmodel=large -mno-red-zone -nostdlib)
add_link_options(-T${LINKER_SCRIPT} -nostdlib -O0)
include_directories("include")

# Deps
add_subdirectory(arch)
add_subdirectory(library)
add_subdirectory(drivers)
add_subdirectory(init)
add_subdirectory(common)
add_subdirectory(helpers)

# Kernel
set_target_properties(PlumberCore PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT} RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_link_libraries(PlumberCore PRIVATE arch_boot arch_multiboot2
                                  library_strmgr library_libfb
                                  driver_bda driver_fb_vga
                                  helper_fb
                                  general_logging general_fbcon)