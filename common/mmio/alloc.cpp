#include <mmio/get_ptr.hpp>
#include <mmio/alloc.hpp>

extern unsigned long long nkernel_end;
unsigned long long index = nkernel_end;
constexpr unsigned char zero = static_cast<unsigned char>('\0');

volatile unsigned char* alloc(const unsigned long long size)
{
    volatile unsigned char *ptr = nullptr;
    while (true)
    {
        bool give_this = true, again = false;
        ptr = uchar_ptr(index);
        for (unsigned long long i = 0; i != size; i++)
        {
            if (*uchar_ptr(index + i) != zero)
            {
                give_this = false;
                continue;
            }
            else if (!give_this)
            {
                index += i;
                again = true;
                break;
            }
        }
        if (give_this)
        {
            for (unsigned long long i = 0; i != size; i++)
                ptr[i] = '\0';
            index += size;
            return ptr;
        }
        else if (!again) index += size;
    }
}

unsigned char* alloc_safe(const unsigned long long size)
{
    return reinterpret_cast<unsigned char*>(*alloc(size));
}

char* asciiz(const unsigned long long size)
{
    return reinterpret_cast<char*>(*alloc(size));
}

unsigned long long ullint()
{
    return *reinterpret_cast<volatile unsigned long long*>(alloc(8));
}

unsigned short* ushort_str(const unsigned short size)
{
    return reinterpret_cast<unsigned short*>(*alloc(size * 2));
}

bool boolean()
{
    return *reinterpret_cast<volatile bool*>(alloc(1));
}