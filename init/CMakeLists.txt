add_executable(PlumberCore main.cpp)

add_custom_command(TARGET PlumberCore POST_BUILD COMMAND grub-file --is-x86-multiboot2 $<TARGET_FILE:PlumberCore>)
add_custom_command(TARGET PlumberCore POST_BUILD COMMAND mv $<TARGET_FILE:PlumberCore> ${CMAKE_BINARY_DIR}/ISO/boot/)
add_custom_command(TARGET PlumberCore POST_BUILD COMMAND grub-mkrescue -o ${CMAKE_BINARY_DIR}/test.iso ${CMAKE_BINARY_DIR}/ISO)
add_custom_command(TARGET PlumberCore POST_BUILD COMMAND qemu-system-x86_64 -machine q35 -cpu host -enable-kvm -m 8192 -cdrom ${CMAKE_BINARY_DIR}/test.iso)