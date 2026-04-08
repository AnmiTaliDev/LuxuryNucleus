#include <mmio/str.hpp>
#include <mmio/ports.hpp>
using namespace MMIO;

extern volatile unsigned long long nkernel_end;
volatile unsigned long long index = nkernel_end + 1;

volatile unsigned char *Strings::alloc(const unsigned long long size)
{
    volatile unsigned char *ptr = nullptr;
    if (size > 1)
    {
        while (true)
        {
            ptr = reinterpret_cast<volatile unsigned char*>(index);
            bool give_this = true;
            for (unsigned long long i = 0; i != size; i++)
            {
                if (ptr[i])
                {
                    index += i + 1;
                    give_this = false;
                    break;
                }
            }
            if (give_this)
                break;
        }
    }
    index += size + 1;
    return ptr;
}

volatile unsigned short *Strings::ushort_asciiz(const volatile unsigned long long &size)
{
    return reinterpret_cast<volatile unsigned short*>(alloc(size * 2));
}

volatile char *Strings::char_asciiz(const volatile unsigned long long &size)
{
    return reinterpret_cast<volatile char*>(alloc(size));
}

void Ports::outb(const volatile unsigned short &port, unsigned char value)
{
    __asm__ volatile
    (
        "out dx, al"
        :
        : "d"(port), "a"(value)
    );
}

unsigned char Ports::inb(const volatile unsigned short &port)
{
    volatile unsigned char data;
    __asm__ volatile
    (
        "in al, dx"
        : "=a" (data)
        : "d" (port)
    );
    return data;
}