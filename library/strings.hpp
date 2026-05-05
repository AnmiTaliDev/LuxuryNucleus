namespace Library
{
    namespace Strings
    {
        extern unsigned length_of(const volatile void *const of_what);
        extern void clean_asciiz(volatile void *const ptr, unsigned &length);
        extern volatile char *to_string(int, bool hex);
    }
}