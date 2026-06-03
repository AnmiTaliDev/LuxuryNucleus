#include <library/strings.hpp>
#include <memory/alloc.hpp>
#include <graphics/fbcon.hpp>
#include <init/services/logger.hpp>
#include "logging.hpp"
using namespace Graphics::fbcon;
using namespace Debug;

namespace LogPrefix
{
    constexpr static const volatile char *const volatile Info = "<*> ";
    constexpr static const volatile char *const volatile Warn = "<!> ";
    constexpr static const volatile char *const volatile Error  = "<E> ";
}

void (*volatile write_char)(const volatile char&) = nullptr;
volatile char *volatile buffer;
constexpr volatile unsigned buffer_size = 1001;
unsigned buffer_len = 0;

static void __write_char_buffer_only(const volatile char &what)
{
    buffer[buffer_len] = what;
    buffer_len++;
    if (buffer_len == buffer_size)
        Library::Strings::clean_asciiz(buffer,buffer_len);
}

static void __write_char_with_fbcon(const volatile char &what)
{
    __write_char_buffer_only(what);
    draw_char_gpu_func(what);
}

static void stub(const volatile char *const)
{}

static void write_str(const volatile char *const volatile &str)
{
    for (unsigned len = 0; str[len]; ++len)
        write_char(str[len]);
}

constexpr static volatile char newline = '\n';
static void write_line(const volatile char *const &str)
{
    write_str(str);
    write_char(newline);
}

static void _info(const volatile char *const text)
{
    write_str(LogPrefix::Info);
    write_line(text);
}

static void _warn(const volatile char *const text)
{
    write_str(LogPrefix::Warn);
    write_line(text);
}

static void _err(const volatile char *const text)
{
    write_str(LogPrefix::Error);
    write_line(text);
}

void (*Logging::info)(const volatile char *const) = stub;
void (*Logging::warn)(const volatile char *const) = stub;
void (*Logging::err)(const volatile char *const) = stub;

void Graphics::fbcon::switch_write_char_func()
{
    for (unsigned len = 0; len != buffer_len; ++len)
        draw_char_gpu_func(buffer[len]);
    write_char = __write_char_with_fbcon;
    Logging::info("exported logs buffer to display");
}

void Logging::init()
{
    //volatile char buff[1001];
    //buffer = buff;
    buffer = static_cast<volatile char*>(Memory::alloc(buffer_size));
    write_char = __write_char_buffer_only;
    info = _info; warn = _warn; err = _err;
    info("[debug/logger]: Initialized buffer of 1001 bytes.");
}