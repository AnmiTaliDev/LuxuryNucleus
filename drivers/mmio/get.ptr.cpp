volatile unsigned short* ushort_ptr(long long addr)
{
    return reinterpret_cast<volatile unsigned short*>(addr);
}