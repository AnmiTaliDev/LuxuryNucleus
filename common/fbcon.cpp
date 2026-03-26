#include <logging.hpp>
#include <helpers/gpu.hpp>
#include <init/fbcon.hpp>
#include <fbcon.hpp>
using namespace Helpers::GPU;

//constexpr char log_prefix[10] = "[fbcon]: ";
void (*fbcon::fb_func)(const char&) = nullptr;

static void set_gpu_helper(void (*func)(const char&)){
    Logging::info("[fbcon]: updating GPU helper...");
    fbcon::fb_func = func;
}

static void choose_primary_gpu()
{
    // Software acceleration
    static SoftwareAccel::instance software_acceleration;
    if (software_acceleration.init)
    {
        Logging::info("[fbcon]: setting up software rendering...");
        set_gpu_helper(SoftwareAccel::draw_char);
    }
}

void fbcon::init()
{
    Logging::info("[fbcon]: initializing, choosing GPU helper...");
    choose_primary_gpu();
    if (fb_func != nullptr)
    {
        Logging::switch_write_char_func();
    }
    else
        Logging::warn("[fbcon]: no active GPU was detected");
}