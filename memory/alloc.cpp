#include "alloc.hpp"

extern char *mmio_addr_alloc_kernel_end asm("mmio_addr_alloc_kernel_end");
char *index = mmio_addr_alloc_kernel_end;

void *Memory::malloc(const unsigned long long &size)
{
    if (size > 1)
    {
        bool give_this; unsigned long long i;
        while (true)
        {
            give_this = true;
            for (i = 0; i != size + 1; ++i)
            {
                if (index[i]) // != zero
                    give_this = false;
                else if (!give_this)
                    break;
            }
            index += i;
            if (give_this)
                break;
        }
    }
    return index;
}

void Memory::free(void *ptr, const unsigned long long &size)
{
    char *str = static_cast<char *>(ptr);
    for (unsigned long long i = 0; i != size; i++)
        str[i] = 0;
}