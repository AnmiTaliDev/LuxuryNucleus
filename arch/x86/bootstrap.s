.intel_syntax noprefix

.set EFLAGS_ID, 1 << 21
.set CPUID_EXTENSIONS, 0x80000000
.set CPUID_EXT_FEATURES, 0x80000001
.set CPUID_EDX_EXT_FEAT_LM, 1 << 29
.set CR0_PAGING, 1 << 31
.set CR4_PAE_ENABLE, 1 << 5
.set SIZEOF_PAGE_TABLE, 4096
.set PML4T_ADDR, 0x1000
.set PDPT_ADDR, 0x2000
.set PDT_ADDR, 0x3000
.set PT_ADDR, 0x4000
.set PT_ADDR_MASK, 0xffffffffff000
.set PT_PRESENT, 1
.set PT_READABLE, 2
.set ENTRIES_PER_PT, 512
.set SIZEOF_PT_ENTRY, 8
.set PAGE_SIZE, 0x1000

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
halt:
    cli
1:  hlt
    jmp 1b

.global _start
.code32
_start:
    mov stack_top, esp
    call init_start
    call halt
