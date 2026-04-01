#include <mmio/alloc.hpp>
#include <fbcon.hpp>
#include <init/logging.hpp>
#include <logging.hpp>

constexpr const char *info_prefix = "<*> ";
constexpr const char *warn_prefix = "<!> ";
constexpr const char *err_prefix  = "<E> ";

volatile char *buffer;
unsigned long long buffer_size = 0;

void __write_char_buffer_only(const char &what)
{
    buffer[buffer_size] = what;
    buffer_size++;
}

void __write_char_with_fbcon(const char &what)
{
    __write_char_buffer_only(what);
    fbcon::draw_char_gpu_func(what);
}

bool Logging::inited;
void (*write_char)(const char&) = nullptr;

void Logging::init()
{
    inited = MMIO::boolean();
    inited = false;
    buffer = MMIO::asciiz(1000);
    write_char = __write_char_buffer_only;
    inited = true;
    info("[logger] Initialized with 1000 bytes of buffer");
}

void fbcon::switch_write_char_func()
{
    for (unsigned long long len = 0; len != buffer_size; len++)
        draw_char_gpu_func(buffer[len]);
    write_char = __write_char_with_fbcon;
    Logging::info("[fbcon]: exported logger buffer to display");
}

void write_str(const char *str)
{
    for (unsigned long long len = 0; str[len]; len++)
        write_char(str[len]);
}

void write_line(const char *&str)
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