namespace Helpers
{
    namespace FB
    {
        namespace VGA_text
        {
            class instance
            {
                public:
                bool init = false;
                instance();
            };
            extern void put_char(const char&);
        };
    }
}