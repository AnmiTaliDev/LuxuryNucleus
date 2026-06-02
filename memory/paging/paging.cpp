#include "paging.hpp"

unsigned int __attribute__((aligned(4096))) page_directory[1024];
unsigned int __attribute__((aligned(4096))) page_table[1024];

static void init_page_dir(unsigned int (&dir)[1024])
{
    for (unsigned int i = 0; i != 1024; ++i)
        dir[i] = 0x2;
}

static void init_page_table(unsigned int (&table)[1024])
{
    for (unsigned int i = 0; i != 1024; ++i)
        table[i] = (i * 0x1000) | 3;
}

static void load_page_dir(unsigned int (&dir)[1024])
{
    asm volatile
    (
        "mov cr3, %0"
        :
        : "r"(dir)
    );
}

static void init_paging()
{
    init_page_dir(page_directory);
    init_page_table(page_table);
    page_directory[0] = reinterpret_cast<unsigned int>(page_table) | 3;
    load_page_dir(page_directory);
}

static void enable_paging()
{
    asm
    (
        "mov eax, cr0\n"
        "or  eax, 0x80000000\n"
        "mov cr0, eax"
    );
}

void Memory::Paging::setup()
{
    init_paging();
    enable_paging();
}