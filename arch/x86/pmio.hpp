namespace Architecture
{
    namespace x86
    {
        extern void out(const unsigned short &port, const char &data);
        extern void in(const unsigned short &port, char &data);
    }
}