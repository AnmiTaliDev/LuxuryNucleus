namespace Library
{
    namespace Str_Int
    {
        extern unsigned length_of(const void *const of_what);
        extern const char *to_string(int, bool hex);
        extern bool same(const void *const first, const void *const second, unsigned size);
        extern int bcd_to_bin(int bcd);
    }
}