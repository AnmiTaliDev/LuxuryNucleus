#include <arch/multiboot2.hpp>

constexpr multiboot_entry_tag entry_tag
{
    .type = 9,
    .size = 16,
    .entry_addr = 0x200000
};

constexpr multiboot_header __attribute__((section(".multiboot"))) multiboot2
{
    .magic     = (unsigned int)multiboot2_magic,
    .arch      = 1,
    .length    = (unsigned int)multiboot2_header_size,
    .checksum  = -((unsigned int)multiboot2_magic + 1 + (unsigned int)multiboot2_header_size),
    .entry_tag = entry_tag,
    .end_tag   = { .type = 0, .size = 8 }
};