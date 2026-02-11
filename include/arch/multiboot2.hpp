struct __attribute__((packed)) multiboot_end_tag
{
    unsigned type;
    unsigned size;
};

struct __attribute__((packed)) multiboot_entry_tag
{
    unsigned type;
    unsigned size;
    unsigned long entry_addr;
};

struct __attribute__((packed)) multiboot_header
{
    unsigned magic;
    unsigned arch;
    unsigned length;
    unsigned checksum;
    multiboot_entry_tag entry_tag;
    multiboot_end_tag end_tag;
};

#define multiboot2_header_size sizeof(multiboot_header)
#define multiboot2_magic       0xE85250D6