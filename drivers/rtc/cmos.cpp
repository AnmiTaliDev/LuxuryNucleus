#include <memory/io/port.hpp>
#include <library/str_int.hpp>
#include <memory/alloc.hpp>
#include "register.hpp"
#include "cmos.hpp"
using namespace Library;
using namespace Memory::IO;
using namespace Drivers;

unsigned short CMOS::pmio_cmos_index_register = 0x70,
               CMOS::pmio_cmos_data_register = 0x71;

enum
{
    second_reg = 0,
    minute_reg = 0x2,
    hour_reg = 0x4
};

static char rtc_reg_get(const char &reg)
{
    Ports::write(CMOS::pmio_cmos_index_register,reg);
    return Ports::read(CMOS::pmio_cmos_data_register);
}

char CMOS::get_second()
{
    return Str_Int::bcd_to_bin(rtc_reg_get(second_reg));
}

char CMOS::get_minute()
{
    return Str_Int::bcd_to_bin(rtc_reg_get(minute_reg));
}

char CMOS::get_hour()
{
    return Str_Int::bcd_to_bin(rtc_reg_get(hour_reg));
}

char *HHMMSS = const_cast<char *>("00:00:00");

char *CMOS::get_HHMMSS_str()
{ // HH:MM:SS
  // 01234567
    const char *HH = Library::Str_Int::to_string(get_hour(),false),
               *MM = Library::Str_Int::to_string(get_minute(),false),
               *SS = Library::Str_Int::to_string(get_second(),false);
    if (!HH[1])
    { HHMMSS[0] = '0'; HHMMSS[1] = HH[0]; }
    else
    { HHMMSS[0] = HH[0]; HHMMSS[1] = HH[1]; }

    HHMMSS[2] = ':';

    if (!MM[1])
    { HHMMSS[3] = '0'; HHMMSS[4] = MM[0]; }
    else
    { HHMMSS[3] = MM[0]; HHMMSS[4] = MM[1]; }

    HHMMSS[5] = ':';

    if (!SS[1])
    { HHMMSS[6] = '0'; HHMMSS[7] = SS[0]; }
    else
    { HHMMSS[6] = SS[0]; HHMMSS[7] = SS[1]; }

    return HHMMSS;
}