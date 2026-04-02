namespace Library
{
    namespace strmgr
    {
        extern unsigned long long size_of(volatile void *of_what);
        extern volatile void* cat(const void *source, void *destination,
            const unsigned long long &src_size,
            const unsigned long long &dst_size);
        extern void clean_asciiz(volatile char *ptr, const unsigned long long &size);
    }
}