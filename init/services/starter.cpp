#include "starter.hpp"
using namespace Initialization;

extern void (*mmio_addr_alloc_initservices_start[])() asm("mmio_addr_alloc_initservices_start");
extern void (*mmio_addr_alloc_initservices_end[])() asm("mmio_addr_alloc_initservices_end");

void Services::startup()
{
    for (void (**unit)() = mmio_addr_alloc_initservices_start;
         unit != mmio_addr_alloc_initservices_end; unit++)
        if (*unit != nullptr)
            (*unit)();
}