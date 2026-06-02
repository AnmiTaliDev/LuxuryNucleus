namespace Library
{
    namespace Strings
    {
        extern unsigned length_of(const volatile void *const of_what);
        extern void clean_asciiz(volatile void *const ptr, unsigned &length);
        extern const volatile char *to_string(int, bool hex);
        extern bool same(const volatile void *const first, const volatile void *const second, unsigned &size);
    }
}