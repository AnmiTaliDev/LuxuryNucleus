#include <arch/kernel_alloc.hpp>
#include "alloc.hpp"

volatile unsigned char *index = reinterpret_cast<volatile unsigned char *>(mmio_addr_alloc_kernel_end);
volatile void *Memory::alloc(const volatile unsigned &size)
{ // dynamic memory allocation
    volatile unsigned char *ptr = nullptr;
    if (size > 1)
    {
        while (true)
        {
            bool give_this = true;
            ptr = index;
            for (unsigned i = 0; i != size; ++i)
            {
                if (ptr[i]) // != zero
                    give_this = false;
                else if (!give_this)
                {
                    ptr += i + 1;
                    break;
                }
            }
            if (give_this)
            {
                index += size;
                break;
            }
        }
    }
    return ptr;
}