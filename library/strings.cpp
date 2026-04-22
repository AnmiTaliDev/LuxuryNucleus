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

constexpr static char itos[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
const volatile char *Strings::to_string(int integer, bool hex)
{
    volatile char *reversed_str = nullptr, *str = nullptr;
    unsigned reversed_index = 0, index = 0, base, size_of_str = 1, int_for_size_evaluate = integer;

    if (integer < 0)
    {
        str[index] = '-';
        index++;
        size_of_str += 1;
        integer = -integer;
    }
    if (hex)
    {
        base = 16;
        str[index] = '0';
        index += 1;
        str[index] = 'x';
        index += 1;
        size_of_str += 2;
    }
    else
        base = 10;

    for (int_for_size_evaluate = integer; int_for_size_evaluate != 0; size_of_str++)
        int_for_size_evaluate = int_for_size_evaluate / base;
    str = reinterpret_cast<volatile char*>(MM::alloc(size_of_str));
    reversed_str = reinterpret_cast<volatile char*>(MM::alloc(size_of_str));

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