namespace Memory
{
    extern void *malloc(const unsigned long long &);
    extern void free(void *,const unsigned long long &);

    template <typename unit_type>
    unit_type* allocate(const unsigned long long &size)
    {
        return static_cast<unit_type *>(malloc(size * sizeof(unit_type)));
    }

    template <typename unit_type>
    [[noreturn]] void clean(unit_type *obj, const unsigned long long &size)
    {
        free(obj, size * sizeof(unit_type));
        free(&obj, sizeof(obj));
    }
}