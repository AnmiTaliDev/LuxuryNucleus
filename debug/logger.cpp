#include <library/str_int.hpp>
#include <memory/alloc.hpp>
#include <graphics/fbcon.hpp>
#include <init/services/logger.hpp>
#include "logging.hpp"
using namespace Graphics::fbcon;
using namespace Debug;

namespace LogPrefix
{
    constexpr static const char *const Info = "<*> ";
    constexpr static const char *const Warn = "<!> ";
    constexpr static const char *const Error  = "<E> ";
}

void (*write_char)(const char&);
char *buffer;
constexpr unsigned buffer_size = 1001;
unsigned buffer_len = 0;

static void __write_char_buffer_only(const char &what)
{
    buffer[buffer_len] = what;
    buffer_len++;
}

static void __write_char_with_fbcon(const char &what)
{
    __write_char_buffer_only(what);
    draw_char_gpu_func(what);
}

static void write_str(const char *const &str)
{
    for (unsigned len = 0; str[len]; ++len)
        write_char(str[len]);
}

static void write_line(const char *const &str)
{
    write_str(str);
    write_char('\n');
}

void Logging::info(const char *const text)
{
    write_str(LogPrefix::Info);
    write_line(text);
}

void Logging::warn(const char *const text)
{
    write_str(LogPrefix::Warn);
    write_line(text);
}

void Logging::err(const char *const text)
{
    write_str(LogPrefix::Error);
    write_line(text);
}


void Graphics::fbcon::switch_write_char_func()
{
    for (unsigned len = 0; len != buffer_len; ++len)
        draw_char_gpu_func(buffer[len]);
    write_char = __write_char_with_fbcon;
    Logging::info("exported logs buffer to display");
}

void Logging::init()
{
    buffer = Memory::allocate<char>(buffer_size);
    write_char = __write_char_buffer_only;
    info("[debug/logger]: Initialized buffer of 1001 bytes.");
}