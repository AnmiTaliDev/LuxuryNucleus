#include <arch/stack.hpp>

alignas(16) __attribute__((section(".bss"))) unsigned char stack[16 * 1024];

unsigned char *const stack_bottom = stack;
unsigned char *const stack_top    = stack + sizeof(stack);