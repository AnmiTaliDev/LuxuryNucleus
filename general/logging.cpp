#include <general/init/logging.hpp>
#include <general/logging/con.hpp>
#include <general/logging/log.hpp>
#include <general/fbcon.hpp>

constexpr const char * const info_prefix = "<*> ";
constexpr const char * const warn_prefix = "<!> ";
constexpr const char * const err_prefix  = "<E> ";

Logging::buffer_instance *Logging::__buffer_instance = nullptr;

Logging::buffer_instance::buffer_instance()
{
    char buff[1024];
    buffer = buff;
    buffer_size = 0;
}

static void __write_char_buffer_only(const char &what)
{
    Logging::__buffer_instance->buffer[Logging::__buffer_instance->buffer_size] = what;
    Logging::__buffer_instance->buffer_size++;
}

static void __write_char_with_fbcon(const char &what)
{
    __write_char_buffer_only(what);
    fbcon::fb_func(what);
}

void (*write_char)(const char&) = __write_char_buffer_only;

char Logging::give_char_loop()
{
    static int len = -1;
    len++;
    return __buffer_instance->buffer[len];
}

void Logging::switch_write_char_func()
{
    write_char = __write_char_with_fbcon;
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