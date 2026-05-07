#include <memory/io/port.hpp>
#include <library/integers.hpp>
#include "register.hpp"
#include "cmos.hpp"
using namespace Library;
using namespace Memory::IO;
using namespace Drivers;

volatile unsigned short CMOS::pmio_cmos_index_register = 0x70,
                        CMOS::pmio_cmos_data_register = 0x71;

enum
{
    second_reg = 0,
    minute_reg = 0x2,
    hours_reg = 0x4
};

static unsigned char rtc_reg_get(const unsigned char &reg)
{
    Ports::write(CMOS::pmio_cmos_index_register,reg);
    return Ports::read(CMOS::pmio_cmos_data_register);
}

unsigned char CMOS::get_second()
{
    return Integers::bcd_to_bin(rtc_reg_get(second_reg));
}

unsigned char CMOS::get_minute()
{
    return Integers::bcd_to_bin(rtc_reg_get(minute_reg));
}