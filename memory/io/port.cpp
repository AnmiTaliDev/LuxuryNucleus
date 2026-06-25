#include <arch/x86/pmio.hpp>
#include "port.hpp"
using namespace Memory::IO;

char Ports::read(const unsigned short &port)
{
    char value;
    Architecture::x86::in(port,value);
    return value;
}

void Ports::write(const unsigned short &port, const char value)
{
    Architecture::x86::out(port,value);
}