#include <library/strings.hpp>
#include <mmio/str.hpp>
#include <fbcon.hpp>
#include <init/logging.hpp>
#include <logging.hpp>

constexpr const volatile char *info_prefix = "<*> ";
constexpr const volatile char *warn_prefix = "<!> ";
constexpr const volatile char *err_prefix  = "<E> ";

volatile char *buffer;
unsigned long long buffer_len = 0;
constexpr volatile unsigned long long buffer_size = 1001;

void __write_char_buffer_only(const volatile char &what)
{
    buffer[buffer_len] = what;
    buffer_len++;
    if (buffer_len == buffer_size)
        Library::Strings::clean_asciiz(buffer,buffer_size);
}

void __write_char_with_fbcon(const volatile char &what)
{
    __write_char_buffer_only(what);
    fbcon::draw_char_gpu_func(what);
}

bool Logging::inited = false;
void (*write_char)(const volatile char&) = nullptr;

void Logging::init()
{
    buffer = MMIO::Strings::char_asciiz(buffer_size);
    write_char = __write_char_buffer_only;
    inited = true;
    info("[logger]: Initialized with 1001 bytes of buffer");
}

void fbcon::switch_write_char_func()
{
    for (unsigned long long len = 0; len != buffer_len; len++)
        draw_char_gpu_func(buffer[len]);
    write_char = __write_char_with_fbcon;
    Logging::info("[fbcon & logger]: exported logs buffer to display");
}

void write_str(const volatile char *str)
{
    for (unsigned long long len = 0; str[len]; len++)
        write_char(str[len]);
}
constexpr volatile char newline = '\n';
void write_line(const volatile char *&str)
{
    write_str(str);
    write_char(newline);
}

void Logging::info(const volatile char *log)
{
    write_str(info_prefix);
    write_line(log);
}

void Logging::warn(const volatile char *log)
{
    write_str(warn_prefix);
    write_line(log);
}

void Logging::err(const volatile char *log)
{
    write_str(err_prefix);
    write_line(log);
}