#include "multiboot2.hpp"
using namespace Architecture::x86::Multiboot2;

constexpr static tag tags_[]
{
    {.type = 0, .flags = 0, .size = 8, .data = {}}
};

constexpr static volatile header __attribute__((section(".multiboot2"),used)) multiboot_hdr
{
    .magic = 0xE85250D6,
    .architecture = 0,
    .length = sizeof(header),
    .checksum = static_cast<unsigned>(-(0xE85250D6 + sizeof(header))),
    .tags = *tags_
};