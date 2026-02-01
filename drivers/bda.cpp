#define mmio_addr_bda (const unsigned short*) 0x410
#include <drivers/bda.hpp>

const unsigned short * const bda_detected_hw = mmio_addr_bda;

enum BDA::video_type BDA::video_type()
{
    return (enum video_type)(*bda_detected_hw & 0x30);
}