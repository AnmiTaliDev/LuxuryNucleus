#include <logging.hpp>
#include <mmio/alloc.hpp>
#include <helpers/gpu.hpp>
#include <init/fbcon.hpp>
#include <fbcon.hpp>
using namespace Helpers::GPU;

//constexpr char log_prefix[10] = "[fbcon]: ";
void (*fbcon::fb_func)(const char&) = nullptr;

void set_gpu_helper(void (*func)(const char&)){
    Logging::info("[fbcon]: updating GPU helper...");
    fbcon::fb_func = func;
}

void choose_primary_gpu()
{
    // Software acceleration
    SoftwareAccel::instance Helper_GPU_SoftwareAccel = *reinterpret_cast<SoftwareAccel::instance*>(*alloc_safe(sizeof(SoftwareAccel::instance*)));
    Helper_GPU_SoftwareAccel = SoftwareAccel::instance();
    if (Helper_GPU_SoftwareAccel.init)
    {
        Logging::info("[fbcon]: setting up software rendering...");
        set_gpu_helper(SoftwareAccel::draw_char);
    }
}

void fbcon::init()
{
    Logging::info("[fbcon]: choosing GPU helper...");
    if (choose_primary_gpu(); fb_func != nullptr)
    {
        switch_write_char_func();
    }
    else
        Logging::warn("[fbcon]: no active GPU was detected");
}