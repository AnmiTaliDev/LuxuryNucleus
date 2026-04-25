#include <mm/alloc.hpp>
#include "strings.hpp"
using namespace Library;

unsigned Strings::length_of(const volatile void *of_what)
{
    const volatile unsigned char *ptr_str = reinterpret_cast<const volatile unsigned char*>(of_what);
    unsigned len = 0;
    while (ptr_str[len])
        len++;
    return len;
}

void Strings::clean_asciiz(volatile void *ptr, unsigned &index)
{
    volatile unsigned char *ptr_str = reinterpret_cast<volatile unsigned char*>(ptr);
    while (index != 0)
    {
        ptr_str[index] = '\0';
        index--;
    }
}

constexpr static volatile char itos[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
volatile char *Strings::to_string(int integer, bool hex)
{
    volatile char *reversed_str = nullptr, *str = nullptr;
    unsigned reversed_index = 0, index = 0, base;

    if (integer < 0)
    {
        str[index] = '-';
        index++;
        integer = -integer;
    }
    if (hex)
    {
        base = 16;
        str[index] = '0';
        index += 1;
        str[index] = 'x';
        index += 1;
    }
    else
        base = 10;

    for (; integer > 0; integer /= base)
    {
        reversed_str[reversed_index] = itos[integer % base];
        reversed_index++;
    }
    while (reversed_index != 0)
    {
        reversed_index--;
        str[index] = reversed_str[reversed_index];
        index++;
    }
    return str;
}