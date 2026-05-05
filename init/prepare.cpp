#include <init/general.hpp>
extern void init_prepare() asm("init_prepare");

void init_prepare()
{
    Initialization::General();
}