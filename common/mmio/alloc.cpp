#include <mmio/get_ptr.hpp>
#include <mmio/alloc.hpp>

extern unsigned long long nkernel_end;
unsigned long long index = nkernel_end;
static unsigned char zero = static_cast<unsigned char>('\0');

volatile unsigned char* asciiz(unsigned long long size)
{
    volatile unsigned char *ptr = nullptr;
    while (true)
    {
        bool give_this = true, again = false;

        for (unsigned long long i = 0; i != size; i++)
        {
            ptr = uchar_ptr(index + i);
            if (*ptr != zero)
            {
                give_this = false;
            }
            else if (!give_this)
            {
                index += i;
                again = true;
                break;
            }
        }

        if (again)
            continue;
        else if (give_this)
        {
            ptr = uchar_ptr(index);
            index += size;
            return ptr;
        }
        else index += size;
    }
}

bool boolean()
{
    return *reinterpret_cast<volatile bool*>(asciiz(1));
}

unsigned long long ullint()
{
    return *reinterpret_cast<volatile unsigned long long*>(asciiz(8));
}