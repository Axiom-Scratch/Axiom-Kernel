#include "vga.h"
#include "idt.h"
#include <sys/types.h>

void kernel_main()
{
    vga_clear();

    vga_print("Welcome to Axiom Kernel\n");

    idt_init();

    vga_print("IDT initalized\n");

    while(1);
}