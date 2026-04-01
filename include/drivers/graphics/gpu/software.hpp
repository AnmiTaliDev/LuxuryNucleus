namespace Drivers
{
    namespace Graphics
    {
        namespace GPU
        {
            class Software
            {
                public:
                bool init;
                void draw_char(const volatile char &);
                void draw_pixel(const volatile char &);
                Software();
            };
        }
    }
}