#include <memory/io/port.hpp>
#include "register.hpp"
#include "cmos.hpp"
using namespace Memory::IO;
using namespace Drivers;

unsigned short CMOS::pmio_cmos_index_register = 0x70,
               CMOS::pmio_cmos_data_register = 0x71;

enum
{
    second_reg = 0x00,
    minute_reg = 0x02
};

unsigned char rtc_reg_get(const unsigned char &reg)
{
    Ports::write(CMOS::pmio_cmos_index_register,reg);
    return Ports::read(CMOS::pmio_cmos_data_register);
}

unsigned CMOS::get_second()
{
    return rtc_reg_get(second_reg);
}