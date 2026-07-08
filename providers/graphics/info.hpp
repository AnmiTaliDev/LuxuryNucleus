namespace Providers
{
    namespace Graphics
    {
        struct GPU_provider_info
        {
            const char *const name;
            bool *const inited;
            void (*const *const func)(const char &);
            void (*const *const init_func)();
        };
    }
}