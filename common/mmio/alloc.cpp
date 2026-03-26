#include <mmio/get_ptr.hpp>
#include <mmio/alloc.hpp>

unsigned long long index = nkernel_end;

volatile unsigned char* asciiz(unsigned long long size)
{
    volatile unsigned char* ptr = nullptr;
    while (true)
    {
        ptr = uchar_ptr(index);
        if (*ptr == '\0')
        {
            bool ye = true;
            for (unsigned long long i = 1; i != size; i++)
            {
                if (*uchar_ptr(index + i) != '\0')
                {
                    ye = false;
                    break;
                }
            }
            if (ye)
            {
                index += size;
                return ptr;
            }   
        }
        index += 1;
    }
}