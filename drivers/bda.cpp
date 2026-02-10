#include <drivers/bda.hpp>

#define mmio_addr_bda reinterpret_cast<const volatile unsigned short*const>(0x410)
const volatile unsigned short * const bda_detected_hw = mmio_addr_bda;

enum BDA::video_type BDA::video_type()
{
    return static_cast<enum video_type>(*bda_detected_hw & 0x30);
}