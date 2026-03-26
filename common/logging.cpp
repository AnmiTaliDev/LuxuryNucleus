#include <mmio/alloc.hpp>
#include <fbcon.hpp>
#include <init/logging.hpp>
#include <logging.hpp>

constexpr const char *info_prefix = "<*> ";
constexpr const char *warn_prefix = "<!> ";
constexpr const char *err_prefix  = "<E> ";

volatile unsigned char* buffer;
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

void (*write_char)(const char&) = nullptr;

void Logging::init()
{
    buffer = asciiz(80000);
    write_char = __write_char_buffer_only;
}

void Logging::switch_write_char_func()
{
    for (unsigned long long len = 0; len != buffer_size; len++)
        fbcon::fb_func(buffer[len]);
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