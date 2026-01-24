#include <general/logging.hpp>
#include <general/fbcon.hpp>

constexpr const char *info_prefix = "<*> ";
constexpr const char *warn_prefix = "<!> ";
constexpr const char *err_prefix  = "<E> ";

char* Logging::buffer;
unsigned Logging::buf_size;

void Logging::_write_char__buffer_only(const char &what)
{
    buffer[buf_size] = what;
    if (buf_size++ == 1024)
        buf_size = 0;
}

void Logging::_write_char__with_fbcon(const char &what)
{
    _write_char__buffer_only(what);
    fbcon::fb_func(what);
}

void (*Logging::write_char)(const char&) = Logging::_write_char__buffer_only;

void Logging::write_str(const char *str)
{
    unsigned len = 0;
    while (str[len])
    {
        write_char(str[len]);
        len++;
    }
}

void Logging::write_line(const char *&str)
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

void Logging::init()
{
    static char _buffer[2048];
    buffer = _buffer;
    buf_size = 0;
    write_char = _write_char__buffer_only;
}