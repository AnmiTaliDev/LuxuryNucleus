namespace Drivers
{
    namespace BDA
    {
        enum vga_display_type
        {
            NONE = 0,
            COLOUR = 0x20,
            MONOCHROME = 0x30,
        };
        extern enum vga_display_type get_vga_display_type();
    }
}