namespace Graphics
{
    namespace fbcon
    {
        extern void (*draw_char_gpu_func)(const char&);
        extern void switch_write_char_func();
    };
}