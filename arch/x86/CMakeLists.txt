add_library(arch_boot OBJECT boot.s)

target_compile_options(arch_boot PRIVATE -masm=intel)