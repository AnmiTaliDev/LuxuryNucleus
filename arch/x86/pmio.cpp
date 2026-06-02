#include <arch/x86/pmio.hpp>

void Architecture::x86::out(const volatile unsigned short &port, const volatile unsigned char &data)
{
    asm volatile
    (
        "out dx, al"
        :
        : "d"(port), "a"(data)
    );
}

void Architecture::x86::in(const volatile unsigned short &port, volatile unsigned char &data)
{
    asm volatile
    (
        "in al, dx"
        : "=a" (data)
        : "d" (port)
    );
}