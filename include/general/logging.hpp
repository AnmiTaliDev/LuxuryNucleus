namespace Logging
{
    extern char* buffer;
    extern unsigned buf_size;
    extern void _write_char__buffer_only(const char &what);
    extern void _write_char__with_fbcon(const char &what);
    extern void (*write_char)(const char &what);
    extern void write_str(const char *&str);
    extern void write_line(const char *&str);
    
    extern void info(const char *log);
    extern void warn(const char *log);
    extern void err(const char *log);
    extern void init();
}