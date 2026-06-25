namespace Architecture
{
    namespace x86
    {
        namespace Multiboot2
        {
            struct tag
            {
                const unsigned short type;
                const unsigned short flags;
                const unsigned size;
            };

            struct __attribute__((packed)) header
            {
                const unsigned magic;
                const unsigned architecture;
                const unsigned length;
                const unsigned checksum;
                const tag tags[];
            };
        }
    }
}

#define TAG(TYPE, FLAGS, SIZE) {.type=TYPE,.flags=FLAGS,.size=SIZE}