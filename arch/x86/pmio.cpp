#include <arch/x86/pmio.hpp>

void Architecture::x86::out(const unsigned short &port, const char &data)
{
    asm volatile
    (
        "out dx, al"
        :
        : "d"(port), "a"(data)
    );
}

void Architecture::x86::in(const unsigned short &port, char &data)
{
    asm volatile
    (
        "in al, dx"
        : "=a" (data)
        : "d" (port)
    );
}