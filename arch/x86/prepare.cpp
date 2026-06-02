#include <memory/paging/paging.hpp>
#include <init/general.hpp>
extern void init_prepare() asm("init_prepare");

void init_prepare()
{
    Memory::Paging::setup();
    Initialization::General();
}