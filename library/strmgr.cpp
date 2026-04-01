#include <mmio/alloc.hpp>
#include <library/strmgr/ports.hpp>
#include <library/strmgr/strings.hpp>
using namespace Library;

void strmgr::outb(unsigned short port, unsigned char value)
{
    __asm__
    ( 
        "outb %b0, %w1"
        :
        : "a"(value), "Nd"(port)
        : "memory"
    );
}

unsigned char strmgr::inb(unsigned short port)
{
    unsigned char data;
    __asm__
    (
        "inb %w1, %b0"
        : "=a"(data)
        : "Nd"(port)
        : "memory"
    );
    return data;
}

unsigned long long strmgr::size_of(volatile void *of_what)
{
    volatile unsigned char *ptr = reinterpret_cast<volatile unsigned char*>(of_what);
    unsigned long long size = 0;
    while (ptr[size])
        size++;
    return size;
}

void* strmgr::cat(const void *src, void *dst, 
    const unsigned long long &src_size,
    unsigned long long &dst_size)
{
    unsigned char *src_ptr = reinterpret_cast<unsigned char*>(&src),
                  *dst_ptr = reinterpret_cast<unsigned char*>(dst),
                  *new_str = reinterpret_cast<unsigned char*>(*MMIO::alloc(dst_size + src_size));
    unsigned long long index = 0, len = 0;
    for (len = 0; len != dst_size; len++)
        new_str[len] = dst_ptr[len];
    index = len;
    for (len = 0; len != src_size; len++)
        new_str[index] = src_ptr[len];
    return reinterpret_cast<void*>(new_str);
}

 