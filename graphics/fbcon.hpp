namespace fbcon
{
    extern void (*volatile draw_char_gpu_func)(const volatile char&);
    extern void switch_write_char_func();
};