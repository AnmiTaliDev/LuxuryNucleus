#define mmio_addr_graphics_fb_vga_text (volatile unsigned short*)0xB8000

namespace VGA
{
    volatile unsigned short* const vga_buffer = mmio_addr_graphics_fb_vga_text;
    // Static VGA text framebuffer info
    constexpr unsigned vga_width  = 80; // shows 79
    constexpr unsigned vga_height = 25; // shows 24

    enum vga_colors
    {
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        MAGENTA = 5,
        BROWN = 6,
        LIGHT_GRAY = 7,
        DARK_GRAY = 8,
        LIGHT_BLUE = 9,
        LIGHT_GREEN = 10,
        LIGHT_CYAN = 11,
        LIGHT_RED = 12,
        LIGHT_MAGENTA = 13,
        LIGHT_BROWN = 14,
        WHITE = 15
    };
    class vga_text_fb
    {
    public:
        bool init = false;
        unsigned int  column;
        unsigned int  row;
        unsigned char color;
        enum vga_colors color_fg;
        enum vga_colors color_bg;
        void newline();
        void set_color(enum vga_colors foreground, enum vga_colors background);
        void put_char_at(const unsigned short &what, const unsigned &X, const unsigned &Y);
        void put_char(const unsigned short &what);
        void clean();
        void scroll();
        vga_text_fb();
    };
    namespace helper
    {
        extern vga_text_fb *fb;
        void fb_func(const char &data);
    }
}

