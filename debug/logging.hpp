namespace Logging
{   
    extern void (*info)(const volatile char *const log);
    extern void (*warn)(const volatile char *const log);
    extern void (*err)(const volatile char *const log);
}