cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)
project(NucleusKernel CXX ASM)

# Options
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/arch/x86/script.ld")
add_compile_options(-Wall -Wextra -O0 -ffreestanding -funsigned-char
                    -fno-signed-char -fno-rtti -fno-exceptions -fno-common -fno-threadsafe-statics
                    -m32 -fno-PIC -mno-red-zone -nostdlib)
add_link_options(-T${LINKER_SCRIPT} -nostdlib -no-pie -O0 -m32)
include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(NucleusKernel init/main.cpp)
set_target_properties(NucleusKernel PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT} RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_custom_command(TARGET NucleusKernel POST_BUILD COMMAND grub-file --is-x86-multiboot2 $<TARGET_FILE:NucleusKernel>)
add_custom_command(TARGET NucleusKernel POST_BUILD COMMAND mv $<TARGET_FILE:NucleusKernel> "${CMAKE_BINARY_DIR}/ISO/boot/")
add_custom_command(TARGET NucleusKernel POST_BUILD COMMAND grub-mkrescue -o "${CMAKE_BINARY_DIR}/TEST.iso" "${CMAKE_BINARY_DIR}/ISO/")
add_custom_command(TARGET NucleusKernel POST_BUILD COMMAND qemu-system-x86_64 -enable-kvm -machine q35 -cpu host -m 4096 -cdrom "${CMAKE_BINARY_DIR}/TEST.iso")

# Deps
add_subdirectory(arch)
add_subdirectory(library)
add_subdirectory(drivers)
add_subdirectory(init)
add_subdirectory(common)
add_subdirectory(helpers)