#include <library/strmgr.hpp>

void Library::strmgr::outb(unsigned short port, unsigned char value)
{
    asm volatile
    ( 
        "outb %b0, %w1"
        :
        : "a"(value), "Nd"(port)
        : "memory"
    );
}

unsigned char Library::strmgr::inb(unsigned short port)
{
    unsigned char data;
    asm volatile
    (
        "inb %w1, %b0"
        : "=a"(data)
        : "Nd"(port)
        : "memory"
    );
    return data;
}
/*
char* Library::strmgr::itos(int integer)
{
    if (integer == 0) return "0";
    bool negative = false;
    if (integer < 0) negative = true;
    char output[12], reversed[12];
    unsigned index = 0, index2 = 0;
    while (true)
    {
        switch (integer % 10)
        {
            case 0:
                reversed[index] = '0';
                break;
            case 1:
                reversed[index] = '1';
                break;
            case 2:
                reversed[index] = '2';
                break;
            case 3:
                reversed[index] = '3';
                break;
            case 4:
                reversed[index] = '4';
                break;
            case 5:
                reversed[index] = '5';
                break;
            case 6:
                reversed[index] = '6';
                break;
            case 7:
                reversed[index] = '7';
                break;
            case 8:
                reversed[index] = '8';
                break;
            case 9:
                reversed[index] = '9';
                break;
        }
        integer = integer / 10;
        if (integer == 0) break;
        index++;
    }
    if (negative)
    {
        reversed[index] = '-';
    } else index--;
    while (index != 0)
    {
        output[index2] = reversed[index];
        index2++; index--;
    }
    return output;
}
*/