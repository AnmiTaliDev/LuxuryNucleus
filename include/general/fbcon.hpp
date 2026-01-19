namespace fbcon
{
    extern void (*fb_func)(const char&);
    extern void update_fb_helper(void (*func)(const char&));
    extern void init();
};