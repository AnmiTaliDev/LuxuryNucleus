#include "multiboot2.hpp"
using namespace Architecture::x86::Multiboot2;

constexpr static unsigned multiboot2_magic = 0xE85250D6;
constexpr static unsigned multiboot2_arch = 0;

constexpr static tag tags_[]
{
    {.type = 0, .flags = 0, .size = 8}
};

constexpr static volatile header __attribute__((section(".multiboot2"),used)) multiboot_hdr
{
    .magic = multiboot2_magic,
    .architecture = multiboot2_arch,
    .length = sizeof(header),
    .checksum = static_cast<unsigned>(-(multiboot2_magic + multiboot2_arch + sizeof(header))),
    .tags = *tags_
};