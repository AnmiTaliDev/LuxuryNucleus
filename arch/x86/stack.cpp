alignas(16) static unsigned char __attribute__((section(".bss"))) stack[16384];

unsigned char *const stack_bottom = stack;
unsigned char *Arch::stack_top = stack + sizeof(stack);