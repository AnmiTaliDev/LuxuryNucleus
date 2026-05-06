#include <arch/kernel_alloc.hpp>
#include "alloc.hpp"

unsigned index = mmio_addr_alloc_kernel_end;
volatile void *Memory::alloc(const volatile unsigned &size)
{ // dynamic memory allocation
    volatile unsigned char *volatile ptr = nullptr;
    if (size > 1)
    {
        bool give_this;
        while (true)
        {
            give_this = true;
            ptr = reinterpret_cast<volatile unsigned char*>(index);
            for (unsigned i = 0; i != size; i++)
            {
                if (ptr[i]) // != zero
                    give_this = false;
                else if (!give_this)
                {
                    index += i + 1;
                    break;
                }
            }
            if (give_this)
            {
                index += size;
                break;
            }
            else index++;
        }
    }
    return ptr;
}