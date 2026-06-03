#include <debug/logging.hpp>
#include <drivers/video/gpu/software.hpp>
#include <init/services/fbcon.hpp>
#include "fbcon.hpp"
using namespace Graphics::fbcon;
using namespace Drivers::Graphics;

//constexpr char log_prefix[10] = "[fbcon]: ";
void (*volatile Graphics::fbcon::draw_char_gpu_func)(const volatile char&) = nullptr;

static void set_gpu_helper(void (*const func)(const volatile char&)){
    Debug::Logging::info("[graphics/fbcon]: setting primary GPU...");
    draw_char_gpu_func = func;
}

static void choose_primary_gpu()
{
    // Software acceleration
    if (GPU::Software::init(); GPU::Software::inited)
    {
        Debug::Logging::info("[graphics/fbcon]: quering software rendering...");
        set_gpu_helper(GPU::Software::draw_char);
    }
}

void Graphics::fbcon::init()
{
    Debug::Logging::info("[graphics/fbcon]: choosing GPU helper...");
    if (choose_primary_gpu(); draw_char_gpu_func != nullptr)
        switch_write_char_func();
    else
        Debug::Logging::warn("[graphics/fbcon]: no active GPU was detected");
}