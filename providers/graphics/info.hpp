namespace Providers
{
    namespace Graphics
    {
        struct GPU_provider_info
        {
            const char *name;
            bool *inited;
            void (*func)(const char &);
            void (*init_func)();
        };
    }
}