#include <library/strings.hpp>
#include <mm/alloc.hpp>
#include <graphics/fbcon.hpp>
#include <init/hooks/logging.hpp>
#include "logging.hpp"

namespace LogPrefix
{
    constexpr static const volatile char *Info = "<*> ";
    constexpr static const volatile char *Warn = "<!> ";
    constexpr static const volatile char *Error  = "<E> ";
}

volatile char *buffer;
constexpr volatile unsigned buffer_size = 1001;
unsigned buffer_len = 0;

bool Logging::inited = false;
void (*write_char)(const volatile char&) = nullptr;

void __write_char_buffer_only(const volatile char &what)
{
    buffer[buffer_len] = what;
    buffer_len++;
    if (buffer_len == buffer_size)
        Library::Strings::clean_asciiz(buffer,buffer_len);
}

void __write_char_with_fbcon(const volatile char &what)
{
    __write_char_buffer_only(what);
    fbcon::draw_char_gpu_func(what);
}

void Logging::init()
{
    if (!inited)
    {
        buffer = reinterpret_cast<volatile char*>(MM::alloc(buffer_size));
        write_char = __write_char_buffer_only;
        inited = true;
        info("[logger]: Initialized with 1001 bytes of buffer");
    }
}

void fbcon::switch_write_char_func()
{
    for (unsigned len = 0; len != buffer_len; len++)
        draw_char_gpu_func(buffer[len]);
    write_char = __write_char_with_fbcon;
    Logging::info("exported logs buffer to display");
}

void write_str(const volatile char *const &str)
{
    for (unsigned len = 0; str[len]; len++)
        write_char(str[len]);
}

constexpr static volatile char newline = '\n';
void write_line(const volatile char *const &str)
{
    write_str(str);
    write_char(newline);
}

void Logging::info(const volatile char *const log)
{
    write_str(LogPrefix::Info);
    write_line(log);
}

void Logging::warn(const volatile char *const log)
{
    write_str(LogPrefix::Warn);
    write_line(log);
}

void Logging::err(const volatile char *const log)
{
    write_str(LogPrefix::Error);
    write_line(log);
}