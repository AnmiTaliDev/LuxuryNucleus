#include <arch/multiboot2.hpp>

constexpr multiboot_header __attribute__((section(".multiboot"))) multiboot2
{
    .magic    = multiboot2_magic,
    .arch     = 1,
    .length   = multiboot2_header_size,
    .checksum = -(multiboot2_magic + 1 + multiboot2_header_size)
};