namespace Drivers
{
    namespace Graphics
    {
        namespace GPU
        {
            class Software
            {
                private:
                void set_fb_helper(void (*)(const char&));
                bool FB_vga_text();
                public:
                bool init = false;
                void (*draw_char)(const char &);
                Software();
            };
        }
    }
}