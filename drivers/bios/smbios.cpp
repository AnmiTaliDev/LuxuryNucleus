#include <library/strings.hpp>
using namespace Library::Strings;

volatile unsigned char *EPS = reinterpret_cast<unsigned char*>(0xF0000);
namespace anchor_str
{
    unsigned bit32_size = 4;
    unsigned bit64_size = 5;
}

unsigned i, len;
unsigned char checksum = 0;

static bool chksum(unsigned char max_len)
{
    for (i = 0; i != max_len; i++)
        checksum += EPS[i];

    return checksum == 0;
}

static bool check_eps()
{
    while (EPS != reinterpret_cast<unsigned char*>(0xFFFFF))
    {
#if ARCH_CAP == 64
        if (same(EPS,"_SM3_",anchor_str::bit64_size))
            if (chksum(EPS[5])) break;
#endif
        if (same(EPS,"_SM_",anchor_str::bit32_size))
            if (chksum(EPS[4])) break;
        EPS += 16;
    }
    if (reinterpret_cast<unsigned>(EPS) == 0x100000)
        return false;
    else
        return true;
}