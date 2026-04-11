#include <arch/stack.hpp>

static volatile unsigned char __attribute__((section(".bss"))) stack[16384];
volatile unsigned char *Architecture::x86::stack_top = &stack[16384];