namespace Memory
{
    extern void *malloc(const unsigned long long &);
    extern void free(void *,const unsigned long long &);

    template <typename mem_unit_type>
    mem_unit_type *allocate(const unsigned long long &size)
    {
        return static_cast<mem_unit_type *>(malloc(size * sizeof(mem_unit_type)));
    }

    template <typename mem_unit_type>
    void clean(mem_unit_type *obj, const unsigned long long &size)
    {
        free(obj, size * sizeof(mem_unit_type));
        free(&obj, sizeof(obj));
    }
}