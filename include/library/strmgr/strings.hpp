namespace Library
{
    namespace strmgr
    {
        extern unsigned long long size_of(volatile void *of_what);
        extern void* cat(const void *source, void *destination,
            const unsigned long long &src_size,
            unsigned long long &dst_size);
    }
}