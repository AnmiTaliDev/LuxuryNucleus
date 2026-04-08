#include <drivers/bda.hpp>
using namespace BDA;

#define mmio_addr_bda 0x410
const volatile unsigned short * const volatile bda_detected_hw = reinterpret_cast<volatile unsigned short *>(mmio_addr_bda);

enum video_type BDA::video_type()
{
    return static_cast<enum video_type>(*bda_detected_hw & 0x30);
}
