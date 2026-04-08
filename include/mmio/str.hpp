namespace MMIO
{
    namespace Strings
    {
        extern volatile unsigned char *alloc(const unsigned long long size);
        extern volatile unsigned short *ushort_asciiz(const volatile unsigned long long &size);
        extern volatile char *char_asciiz(const volatile unsigned long long &size);
    }
}