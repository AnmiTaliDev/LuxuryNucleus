#include <memory/io/port.hpp>
#include <drivers/rtc/register.hpp>
#include "nmi.hpp"
using namespace Memory::IO;
using namespace Drivers;

void Interrupt::NMI::enable()
{
    Ports::write(CMOS::pmio_cmos_index_register, Ports::read(CMOS::pmio_cmos_index_register) & 0x7F);
    Ports::read(CMOS::pmio_cmos_data_register);
}

void Interrupt::NMI::disable()
{
    Ports::write(CMOS::pmio_cmos_index_register, Ports::read(CMOS::pmio_cmos_index_register) | 0x80);
    Ports::read(CMOS::pmio_cmos_data_register);
}