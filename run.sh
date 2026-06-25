cmake -S .. -B . -Darch=x86 -Darch_bit_capacity=32 || exit 1
cmake --build . || exit 1
sync
mv arch/lnucleus.elf ISO/boot/
grub-mkrescue -o test.iso ISO/
sync
qemu-system-x86_64 -enable-kvm -machine q35 -m 4G -cdrom test.iso
