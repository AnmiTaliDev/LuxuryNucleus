namespace Memory
{
    namespace IO
    {
        namespace Ports
        {
            extern void write(const volatile unsigned short &port, const unsigned char value);
            extern unsigned char read(const volatile unsigned short &port);
        }
    }
}