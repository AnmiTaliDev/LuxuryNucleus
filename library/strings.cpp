#include <mmio/str.hpp>
#include <library/strings.hpp>
using namespace Library;

unsigned long long Strings::length_of(const volatile void *of_what)
{
    const volatile unsigned char *ptr_str = reinterpret_cast<const volatile unsigned char*>(of_what);
    unsigned long long len = 0;
    while (ptr_str[len])
        len++;
    return len;
}

void Strings::clean_asciiz(volatile void *ptr, const volatile unsigned long long &size)
{
    volatile unsigned char *ptr_str = reinterpret_cast<volatile unsigned char*>(ptr);
    for (unsigned long long i = 0; i != size; i++)
        ptr_str[i] = '\0';
}

constexpr static char itos[10] = {'0','1','2','3','4','5','6','7','8','9'};
constexpr volatile unsigned long long str_size = 100;

const volatile char *Strings::to_string(int integer)
{
    volatile char *reversed_str = MMIO::Strings::char_asciiz(str_size),
                  *str          = MMIO::Strings::char_asciiz(str_size);
    unsigned long long reversed_index = 0, index = 0;
    if (integer < 0)
    {
        str[index] = '-';
        index++;
        integer = -integer;
    }
    while (true)
    {
        reversed_str[reversed_index] = itos[integer % 10];
        reversed_index++;
        integer = integer / 10;
        if (integer == 0)
            break;
    }
    while (reversed_index != 0)
    {
        reversed_index--;
        str[index] = reversed_str[reversed_index];
        index++;
    }
    return str;
}