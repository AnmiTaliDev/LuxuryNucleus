struct multiboot_header
{
    unsigned long magic;
    unsigned long arch;
    unsigned long length;
    unsigned long checksum;
} __attribute__((packed, aligned(8)));

#define multiboot2_header_size sizeof(multiboot_header)
#define multiboot2_magic       0xE85250D6