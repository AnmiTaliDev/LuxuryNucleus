namespace Helpers
{
    namespace GPU
    {
        namespace SoftwareAccel
        {
            class instance
            {
                public:
                bool init = false;
                instance();
            };
            extern void draw_char(const char&);
        }
    }
}