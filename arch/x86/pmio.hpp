namespace Architecture
{
    namespace x86
    {
        extern void out(const volatile unsigned short &port, const volatile unsigned char &data);
        extern void in(const volatile unsigned short &port, volatile unsigned char &data);
    }
}