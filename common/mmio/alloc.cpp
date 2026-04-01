#include <mmio/alloc.hpp>
using namespace MMIO;

extern unsigned long long nkernel_end;
constexpr static volatile unsigned char zero = static_cast<unsigned char>('\0');

volatile unsigned char* MMIO::alloc(const unsigned long long size)
{ // dynamic memory allocation
    volatile unsigned char *ptr = nullptr;
    unsigned long long index = nkernel_end;
    if (size > 1)
    {
        while (true)
        {
            bool give_this = true;
            ptr = reinterpret_cast<volatile unsigned char*>(index);
            for (unsigned long long i = 0; i != size; i++)
            {
                if (ptr[i]) // != zero
                    give_this = false;
                else if (!give_this)
                {
                    index += i;
                    break;
                }
            }
            if (give_this)
                break;
            else index += size + 1;
        }
    }
    return ptr;
}

volatile char* MMIO::asciiz(const unsigned long long size)
{
    return reinterpret_cast<volatile char*>(alloc(size));
}

volatile unsigned short* MMIO::ushort_str(const unsigned short size)
{
    return reinterpret_cast<volatile unsigned short*>(alloc(size * 2));
}

volatile unsigned long long* MMIO::ull_int()
{
    return reinterpret_cast<volatile unsigned long long*>(alloc(8));
}

volatile bool* MMIO::boolean()
{
    return reinterpret_cast<volatile bool*>(alloc(1));
}

void clean(volatile unsigned char *ptr, unsigned long long &size)
{
    for (unsigned long long i = 0; i != size; i++)
        ptr[i] = zero;
}

void MMIO::clean_ptr(volatile void *what, unsigned long long &size)
{
    volatile unsigned char *ptr = reinterpret_cast<volatile unsigned char*>(&what);
    return clean(ptr,size);
}

void MMIO::clean_at(volatile unsigned long long address, unsigned long long &size)
{
    volatile unsigned char *ptr = reinterpret_cast<volatile unsigned char*>(address);
    return clean(ptr,size);
}