#include <arch/multiboot2.hpp>

constexpr static unsigned multiboot2_magic = 0xE85250D6;
constexpr static unsigned multiboot2_arch = 0;

constexpr static volatile multiboot2_header multiboot_hdr
{
    .magic = multiboot2_magic,
    .architecture = multiboot2_arch,
    .length = sizeof(multiboot2_header),
    .checksum  = -(multiboot2_magic + multiboot2_arch + sizeof(multiboot2_header)),
    .tags = {{.type = 0, .flags = 0, .size = 8}}
};