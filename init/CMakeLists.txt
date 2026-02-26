add_executable(PlumberCore main.cpp)

add_custom_command(TARGET PlumberCore POST_BUILD COMMAND grub-file --is-x86-multiboot2 $<TARGET_FILE:PlumberCore>)
add_custom_command(TARGET PlumberCore POST_BUILD COMMAND cp $<TARGET_FILE:PlumberCore> ${CMAKE_BINARY_DIR}/ISO/boot/)
add_custom_command(TARGET PlumberCore POST_BUILD COMMAND grub-mkrescue -o ${CMAKE_BINARY_DIR}/test.iso ${CMAKE_BINARY_DIR}/ISO)
add_custom_command(TARGET PlumberCore POST_BUILD COMMAND qemu-system-x86_64 -m 8192 -drive file=${CMAKE_BINARY_DIR}/test.iso)