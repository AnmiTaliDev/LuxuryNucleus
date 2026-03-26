add_executable(NucleusKernel main.cpp)

add_custom_command(TARGET NucleusKernel POST_BUILD COMMAND grub-file --is-x86-multiboot2 $<TARGET_FILE:NucleusKernel>)
add_custom_command(TARGET NucleusKernel POST_BUILD COMMAND mv $<TARGET_FILE:NucleusKernel> "${CMAKE_BINARY_DIR}/ISO/boot/")
add_custom_command(TARGET NucleusKernel POST_BUILD COMMAND grub-mkrescue -o "${CMAKE_BINARY_DIR}/TEST.iso" "${CMAKE_BINARY_DIR}/ISO/")
add_custom_command(TARGET NucleusKernel POST_BUILD COMMAND qemu-system-x86_64 -enable-kvm -cpu host -m 8192 -cdrom "${CMAKE_BINARY_DIR}/TEST.iso")