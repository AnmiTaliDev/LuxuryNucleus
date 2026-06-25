#include <library/str_int.hpp>
#include <memory/alloc.hpp>
using namespace Library::Str_Int;

char *EPS = reinterpret_cast<char *>(0xF0000);

enum
{
    bit32_size = 4,
    bit64_size = 5
};

unsigned i, len;
char checksum = 0;

static bool chksum(char max_len)
{
    for (i = 0; i != max_len; i++)
        checksum += EPS[i];

    return checksum == 0;
}

static bool check_eps()
{
    while (EPS != reinterpret_cast<char *>(0xFFFFF))
    {
#if ARCH_CAP == 64
        if (same(EPS,"_SM3_",bit64_size))
            if (chksum(EPS[5])) break;
#endif
        if (same(EPS,"_SM_",bit32_size))
            if (chksum(EPS[4])) break;
        EPS += 16;
    }
    if (reinterpret_cast<unsigned>(EPS) == 0x100000)
        return false;
    else
        return true;
}