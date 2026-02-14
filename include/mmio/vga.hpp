#define mmio_addr_vga_text_fb_colour     reinterpret_cast<volatile unsigned short*>(0xB8000)
#define mmio_addr_vga_text_fb_monochrome reinterpret_cast<volatile unsigned short*>(0xB0000)
#define mmio_addr_vga_graphics_fb        reinterpret_cast<volatile unsigned char*>(0xA0000)