section .multiboot
align 4
dd 0x1BADB002
dd 0
dd -(0x1BADB002)

section .bss
align 16
stack_bottom:
resb 16384
stack_top:

section .text
extern kernel_main
global _start

_start:
    mov esp, stack_top

    call kernel_main

    cli
hang:
    hlt
    jmp hang