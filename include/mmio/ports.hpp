namespace MMIO
{
    namespace Ports
    {
        extern void outb(const volatile unsigned short &port, unsigned char value);
        extern unsigned char inb(const volatile unsigned short &port);
    }
}