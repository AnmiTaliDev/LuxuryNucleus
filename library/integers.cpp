#include "integers.hpp"
using namespace Library;

unsigned Integers::bcd_to_bin(unsigned bcd)
{
    return (bcd & 0xF) + ((bcd / 16) * 10);
}