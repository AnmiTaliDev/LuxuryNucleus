#define MULTIBOOT2_MAGIC static_cast<unsigned int>(0xE85250D6)
#define MULTIBOOT2_ARCH  static_cast<unsigned int>(0)

namespace Arch
{
    struct __attribute__((packed)) multiboot2_entry
    {
        unsigned short type = 3;
        unsigned short flags = 0;
        unsigned int size;
        unsigned int entry_addr;
    };

    struct __attribute__((packed)) multiboot2_end
    {
        unsigned short type = 0;
        unsigned short flags = 0;
        unsigned int   size = 8;
    };

    struct __attribute__((packed)) multiboot2
    {
        unsigned int magic = MULTIBOOT2_MAGIC;
        unsigned int architecture = MULTIBOOT2_ARCH;
        unsigned int length;
        unsigned int checksum;
        multiboot2_entry entry_tag;
        multiboot2_end end_tag = {};
    };
}

#define MULTIBOOT2_SIZE static_cast<unsigned int>(sizeof(Arch::multiboot2))