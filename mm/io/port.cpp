#include <arch/x86/pmio.hpp>
#include "port.hpp"
using namespace MM::IO;

unsigned char Ports::read(const volatile unsigned short &port)
{
    volatile unsigned char value = '\0';
    Architecture::x86::in(port,value);
    return value;
}

void Ports::write(const volatile unsigned short &port, const unsigned char value)
{
    Architecture::x86::out(port,value);
}