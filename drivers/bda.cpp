#define mmio_addr_bda (const unsigned short*) 0x410
#include <drivers/bda.hpp>

const unsigned short *bda_detected_hw = mmio_addr_bda;

enum video_type BDA::get_video_type()
{
    return (enum video_type) (*bda_detected_hw & 0x30);
}