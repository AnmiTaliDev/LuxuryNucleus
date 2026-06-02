#define INIT_SERVICE(FUNCTION) \
void __attribute__((section(".init_services"),used)) (*const __service_init_ ## FUNCTION)() = FUNCTION;
