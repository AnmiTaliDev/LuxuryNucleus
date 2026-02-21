constexpr static const char * const info_prefix = "<*> ";
constexpr static const char * const warn_prefix = "<!> ";
constexpr static const char * const err_prefix  = "<E> ";

char* buffer;
unsigned long long buffer_size = 0;

static void __write_char_buffer_only(const char &what)
{
    buffer[buffer_size] = what;
    buffer_size++;
}

static void __write_char_with_fbcon(const char &what)
{
    __write_char_buffer_only(what);
    fbcon::fb_func(what);
}

static void (*write_char)(const char&) = __write_char_buffer_only;

void Logging::init()
{
    static char buff[8192];
    buffer = buff;
}

void Logging::switch_write_char_func()
{
    write_char = __write_char_with_fbcon;
    unsigned len = 0;
    while (len != buffer_size)
    {
        fbcon::fb_func(buffer[len]);
        len++;
    }
}

static void write_str(const char *str)
{
    unsigned len = 0;
    while (str[len])
    {
        write_char(str[len]);
        len++;
    }
}

static void write_line(const char *&str)
{
    write_str(str);
    write_char('\n');
}

void Logging::info(const char *log)
{
    write_str(info_prefix);
    write_line(log);
}

void Logging::warn(const char *log)
{
    write_str(warn_prefix);
    write_line(log);
}

void Logging::err(const char *log)
{
    write_str(err_prefix);
    write_line(log);
}