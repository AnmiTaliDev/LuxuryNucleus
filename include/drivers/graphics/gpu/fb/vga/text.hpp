#include <misc/vga_colors.hpp>
using namespace Miscellaneous::FB::VGA;

namespace Drivers
{
    namespace Graphics
    {
        namespace FB
        {
            namespace VGA
            {
                class vga_text_fb
                {
                    public:
                    bool init = false;
                    unsigned short attribute, X, Y;
                    void put_entry(const unsigned short);
                    void put_char(const unsigned short &);
                    void set_attr(const enum vga_colors &, const enum vga_colors &, const bool &);
                    void enable_cursor(const unsigned char &high_scanline, const unsigned char &low_scanline);
                    void disable_cursor();
                    void scroll();
                    void fill_with_zeros();
                    void clean();
                    vga_text_fb();
                };
            }
        }
    }
}