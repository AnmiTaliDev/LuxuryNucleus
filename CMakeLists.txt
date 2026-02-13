cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
project(PlumberCore CXX ASM)
enable_language(ASM)

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/arch/x86/script.ld")
add_compile_options(-Wall -Wextra -O0 -ffreestanding -funsigned-char -fno-rtti -fno-exceptions -fno-threadsafe-statics -fno-signed-char -fpermissive -fno-common -m32 -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -nostdlib)
add_link_options(-T${LINKER_SCRIPT} -z noexecstack -nostdlib -O0 -m32)
include_directories("include")

# Deps
add_library(arch_boot OBJECT arch/x86/boot.s)
add_library(library_strmgr OBJECT library/strmgr.cpp)
add_library(library_libfb OBJECT library/libfb.cpp)
add_library(driver_bda OBJECT drivers/bda.cpp)
add_library(driver_fb_vga OBJECT drivers/graphics/fb/vga.cpp)
add_library(helper_fb OBJECT general/helpers/fb.cpp)
add_library(general_logging OBJECT general/logging.cpp)
add_library(general_fbcon OBJECT general/fbcon.cpp)

# Kernel
add_executable(pcore.elf general/init/main.cpp)
set_target_properties(pcore.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
target_link_libraries(pcore.elf PRIVATE arch_boot
                                library_strmgr library_libfb
                                driver_bda driver_fb_vga
                                helper_fb
                                general_logging general_fbcon) # Deps

# Test
#add_custom_command(TARGET pcore.elf POST_BUILD COMMAND qemu-system-x86_64 -kernel pcore.elf)
add_custom_command(TARGET pcore.elf POST_BUILD COMMAND cp pcore.elf ../ISO/boot/)
add_custom_command(TARGET pcore.elf POST_BUILD COMMAND grub-mkrescue -o test.iso ../ISO)
add_custom_command(TARGET pcore.elf POST_BUILD COMMAND qemu-system-x86_64 -machine q35 -cpu host -enable-kvm -m 128 -cdrom test.iso)
#add_custom_command(TARGET pcore.elf POST_BUILD COMMAND qemu-system-x86_64 -bios /usr/share/edk2-ovmf/OVMF_CODE.fd -cdrom test.iso)