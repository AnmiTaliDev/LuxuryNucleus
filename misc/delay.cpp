#include <drivers/rtc/cmos.hpp>
#include "delay.hpp"
using namespace Miscellaneous;

void Utilities::delay(unsigned s)
{
    unsigned elapsed = 0, rtc_sec = Drivers::CMOS::get_second();

    while (elapsed != s)
    {
        while (rtc_sec == Drivers::CMOS::get_second())
        {}
        rtc_sec = Drivers::CMOS::get_second();
        elapsed++;
    }
}