bits 64

global isr0
global isr32

extern isr0_handler
extern isr32_handler

section .text

isr0:
    push rbp
    mov rbp, rsp
    call isr0_handler
    pop rbp
    iretq

isr32:
    push rbp
    mov rbp, rsp
    call isr32_handler
    pop rbp
    iretq
