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

            struct header
            {
                const unsigned magic;
                const unsigned architecture;
                const unsigned length;
                const unsigned checksum;
                const unsigned long long tags;
            };
        }
    }
}