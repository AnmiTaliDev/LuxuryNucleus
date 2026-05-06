#include <memory/alloc.hpp>
#include "strings.hpp"
using namespace Library;

unsigned Strings::length_of(const volatile void *const of_what)
{
    const volatile unsigned char *const volatile ptr_str = static_cast<const volatile unsigned char*>(of_what);
    unsigned index = 0;
    while (ptr_str[index])
        index++;
    return index;
}

void Strings::clean_asciiz(volatile void *const ptr, unsigned &index)
{
    volatile unsigned char *const volatile ptr_str = static_cast<volatile unsigned char*>(ptr);
    while (index != 0)
    {
        ptr_str[index] = '\0';
        index--;
    }
}

constexpr static volatile char base_num[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
constexpr static unsigned size_of_str = 10;
const volatile char *Strings::to_string(int integer, bool hex)
{
    volatile char *volatile reversed_str = static_cast<volatile char*>(Memory::alloc(size_of_str)), 
                  *volatile          str = static_cast<volatile char*>(Memory::alloc(size_of_str));
    unsigned reversed_index = 0, index = 0, base;

    if (integer < 0)
    {
        str[index] = '-';
        index++;
        integer = -integer;
    }
    else if (integer == 0)
        return static_cast<const volatile char*>("0");

    if (hex)
    {
        base = 16;
        str[index] = '0';
        index++;
        str[index] = 'x';
        index++;
    }
    else
        base = 10;

    for (; integer > 0; integer /= base)
    {
        reversed_str[reversed_index] = base_num[integer % base];
        reversed_index++;
    }

    while (reversed_index > 0)
    {
        reversed_index--;
        str[index] = reversed_str[reversed_index];
        index++;
    }

    return str;
}