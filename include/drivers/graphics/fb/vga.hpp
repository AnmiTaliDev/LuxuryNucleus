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
        unsigned short attribute;
        void put_entry(const unsigned short &entry);
        void put_char(const unsigned short &what);
        void set_attr(const enum vga_colors &foreground, const enum vga_colors &background, const bool &blink);
        void scroll();
        void fill_with_zeros();
        void clean();
        vga_text_fb();
    };
    /*class vga_graphics_fb
    {
        public:
        bool init = false;
        unsigned column, row;
    };*/
}