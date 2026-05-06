namespace Architecture
{
    namespace x86
    {
        namespace Multiboot2
        {
            struct tag_data
            {
                unsigned data;
            };

            struct tag
            {
                const unsigned short type;
                const unsigned short flags;
                const unsigned size;
                const tag_data data[];
            };

            struct header
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