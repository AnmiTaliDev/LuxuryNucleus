#include <memory/alloc.hpp>
#include "str_int.hpp"
using namespace Library;

unsigned Str_Int::length_of(const void *const of_what)
{
    const char *const ptr_str = static_cast<const char*>(of_what);
    unsigned index = 0;
    while (ptr_str[index])
        index++;
    return index;
}

constexpr static char base_num[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
unsigned for_alloc_size, alloc_size;
const char *Str_Int::to_string(int integer, bool hex)
{
    if (integer == 0)
        return "0";

    char *reversed_str, *str;
    unsigned reversed_index = 0, index = 0, base;

    for_alloc_size = integer;

    for (alloc_size = 1; for_alloc_size != 0; alloc_size++)
        for_alloc_size /= 10;
    
    str = Memory::allocate<char>(alloc_size);
    reversed_str = Memory::allocate<char>(alloc_size);

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

bool Str_Int::same(const void *const first, const void *const second, unsigned size)
{
    const char *const f_str = static_cast<const char*>(first);
    const char *const s_str = static_cast<const char*>(second);
    bool same = true;
    unsigned len = 0;

    while (len != size)
    {
        if (f_str[len] == s_str[len]) len++;
        else 
        {
            same = false;
            break;
        }
    }
    return same;
}

int Str_Int::bcd_to_bin(int bcd)
{
    return (bcd & 0xF) + ((bcd / 16) * 10);
}