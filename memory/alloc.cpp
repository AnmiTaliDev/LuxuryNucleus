#include <arch/alloc/kernel.hpp>
#include "alloc.hpp"

char *index = mmio_addr_alloc_kernel_end;

void *Memory::malloc(const unsigned long long &size)
{
    char *ptr;
    if (size > 1)
    {
        bool give_this; unsigned long long i;
        while (true)
        {
            give_this = true;
            ptr = index;
            for (i = 0; i != size + 1; ++i)
            {
                if (ptr[i]) // != zero
                    give_this = false;
                else if (!give_this)
                    break;
            }
            index += i;
            if (give_this)
                break;
        }
    }
    return ptr;
}

void Memory::free(void *ptr, const unsigned long long &size)
{
    char *str = static_cast<char *>(ptr);
    for (unsigned long long i = 0; i != size; i++)
        str[i] = 0;
}