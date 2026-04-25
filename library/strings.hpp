namespace Library
{
    namespace Strings
    {
        extern unsigned length_of(const volatile void *of_what);
        extern void clean_asciiz(volatile void *ptr, unsigned &length);
        extern volatile char *to_string(int, bool hex);
    }
}