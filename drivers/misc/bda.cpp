#include <drivers/bda.hpp>
using namespace BDA;

#define mmio_addr_bda 0x410
const unsigned short * const bda_detected_hw = reinterpret_cast<unsigned short *>(0x410);

enum video_type BDA::video_type()
{
    return static_cast<enum video_type>(*bda_detected_hw & 0x30);
}
