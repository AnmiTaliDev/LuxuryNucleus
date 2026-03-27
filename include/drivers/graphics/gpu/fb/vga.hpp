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
        }
    }
}