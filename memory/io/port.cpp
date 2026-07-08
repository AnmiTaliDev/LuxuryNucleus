#include <arch/x86/pmio.hpp>
#include "port.hpp"
using namespace Memory::IO;

char Ports::read(const unsigned short &port)
{
    char value;
#if defined(__x86_64) || defined(__i386)
    Architecture::x86::in(port,value);
#endif
    return value;
}

void Ports::write(const unsigned short &port, const char &value)
{
#if defined(__x86_64) || defined (__i386)
    Architecture::x86::out(port,value);
#endif
}