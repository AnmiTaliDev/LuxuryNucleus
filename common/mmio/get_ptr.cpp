#include <mmio/get_ptr.hpp>

volatile unsigned char* uchar_ptr(unsigned long long addr)
{
    return reinterpret_cast<volatile unsigned char*>(addr);
}

volatile unsigned short* ushort_ptr(unsigned long long addr)
{
    return reinterpret_cast<volatile unsigned short*>(addr);
}