namespace MMIO
{
    extern volatile unsigned char* alloc(const unsigned long long size);
    extern volatile char* asciiz(const unsigned long long size);
    extern volatile unsigned short* ushort_str(const unsigned short size);
    extern volatile unsigned long long* ull_int();
    extern volatile bool* boolean();
    extern void clean_ptr(volatile void *ptr, unsigned long long &size);
    extern void clean_at(volatile unsigned long long address, unsigned long long &size);
}