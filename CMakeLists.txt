cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 17)
project(GVATC CXX ASM)
enable_language(ASM)

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/arch/x86/script.ld")
add_compile_options(-m32 -ffreestanding -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wall -Wextra -O0)
add_link_options(-m32 -T${LINKER_SCRIPT} -z noexecstack -nostdlib -O0)
include_directories("include")

# Deps
add_library(arch_multiboot2 OBJECT arch/x86/boot.s)
#add_library(arch_pvh_note OBJECT arch/x86/pvh/head.s)
add_library(library_libfb OBJECT library/libfb.cpp)
add_library(driver_bda OBJECT drivers/bda.cpp)
add_library(driver_fb_vga OBJECT drivers/graphics/fb/vga.cpp)
add_library(helper_fb OBJECT general/helpers/fb.cpp)
add_library(general_logging OBJECT general/logging.cpp)
add_library(general_fbcon OBJECT general/fbcon.cpp)

# Kernel
add_executable(PlumberCore general/init/main.cpp)
set_target_properties(PlumberCore PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
target_link_libraries(PlumberCore PRIVATE arch_multiboot2 #arch_pvh_note
                                  library_libfb
                                  driver_bda driver_fb_vga
                                  helper_fb
                                  general_logging general_fbcon) # Deps

# Test
#add_custom_command(TARGET PlumberCore POST_BUILD COMMAND qemu-system-x86_64 -kernel PlumberCore)
add_custom_command(TARGET PlumberCore POST_BUILD COMMAND cp PlumberCore ../ISO/boot/)
add_custom_command(TARGET PlumberCore POST_BUILD COMMAND grub-mkrescue -o test.iso ../ISO)
add_custom_command(TARGET PlumberCore POST_BUILD COMMAND qemu-system-x86_64 -machine q35 -cpu host -enable-kvm -m 128 -cdrom test.iso)
#add_custom_command(TARGET PlumberCore POST_BUILD COMMAND qemu-system-x86_64 -bios /usr/share/edk2-ovmf/OVMF_CODE.fd -cdrom test.iso)