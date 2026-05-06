#include "bda.hpp"
using namespace Drivers;
#include <debug/logging.hpp>
#include <library/strings.hpp>

#define mmio_addr_bda 0x410
const volatile unsigned short *const volatile bda_detected_hw = reinterpret_cast<volatile unsigned short *>(mmio_addr_bda);

enum BDA::vga_display_type BDA::get_vga_display_type()
{
    return static_cast<enum vga_display_type>(*bda_detected_hw & 0x30);
}