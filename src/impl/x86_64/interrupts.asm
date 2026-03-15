bits 64

global isr0
global isr32
global isr33

extern isr0_handler
extern isr32_handler
extern isr33_handler

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

isr33:
    push rbp
    mov rbp, rsp
    call isr33_handler
    pop rbp
    iretq
