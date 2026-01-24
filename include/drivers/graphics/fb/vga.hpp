namespace VGA
{
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
        void set_color(const enum vga_colors &foreground, const enum vga_colors &background);
        void put_entry_at(const unsigned short &entry, const unsigned &X, const unsigned &Y);
        void put_char(const unsigned char &what);
        void clean();
        void scroll();
        vga_text_fb();
    };
}