.set EFLAGS_ID, 1 << 21
.set CPUID_EXTENSIONS, 0x80000000
.set CPUID_EXT_FEATURES, 0x80000001
.set CPUID_EDX_EXT_FEAT_LM, 1 << 29

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.code32
_start:
    mov $stack_top, %esp
    call init_start
