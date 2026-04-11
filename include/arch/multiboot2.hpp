namespace Architecture
{
    namespace x86
    {
        namespace Multiboot2
        {
            struct tag
            {
                unsigned short type;
                unsigned short flags;
                unsigned size;
            };

            struct header
            {
                unsigned magic;
                unsigned architecture;
                unsigned length;
                unsigned checksum;
                tag tags[];
            };
        }
    }
}