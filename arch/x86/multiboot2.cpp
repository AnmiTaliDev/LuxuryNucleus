/* Multiboot2 Specification
   https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html */

Arch::multiboot2_entry entry_tag
{
    .size = sizeof(Arch::multiboot2_entry),
    .entry_addr = 0x200000
};

Arch::multiboot2 __attribute__((section(".multiboot"))) header
{
    .length = MULTIBOOT2_SIZE,
    .checksum = -(MULTIBOOT2_MAGIC + MULTIBOOT2_ARCH + MULTIBOOT2_SIZE),
    .entry_tag = entry_tag
};