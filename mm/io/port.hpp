namespace MM
{
    namespace IO
    {
        namespace Ports
        {
            extern void write(const volatile unsigned short &port, unsigned char value);
            extern unsigned char read(const volatile unsigned short &port);
        }
    }
}