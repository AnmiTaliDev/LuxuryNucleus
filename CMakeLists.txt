cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 17)
project(GVATC CXX ASM)
enable_language(ASM)

add_compile_options(-ffreestanding -fno-threadsafe-statics -Wall -Wextra -m32)
add_link_options(-z noexecstack -nostdlib -m32 -s)
include_directories("include")

# Deps
add_library(driver_bda OBJECT drivers/bda.cpp)
add_library(driver_fb_vga OBJECT drivers/graphics/fb/vga.cpp)
add_library(general_logging OBJECT general/logging.cpp)
add_library(general_fbcon OBJECT general/fbcon.cpp)

# Kernel
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/arch/x86/link.ld")
add_executable(PlumberCore arch/x86/boot.s general/init/main.cpp)
set_target_properties(PlumberCore PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
target_link_options(PlumberCore PRIVATE -T${LINKER_SCRIPT}) # Link
target_link_libraries(PlumberCore PRIVATE general_logging general_fbcon driver_bda driver_fb_vga) # Deps

# Test
add_custom_command(TARGET PlumberCore POST_BUILD COMMAND qemu-system-x86_64 -kernel PlumberCore)
