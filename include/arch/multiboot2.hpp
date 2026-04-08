struct multiboot2_tag
{
    unsigned short type;
    unsigned short flags;
    unsigned size;
};

struct multiboot2_header
{
    unsigned magic;
    unsigned architecture;
    unsigned length;
    unsigned checksum;
    multiboot2_tag tags[];
};