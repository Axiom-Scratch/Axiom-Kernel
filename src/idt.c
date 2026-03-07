#include "idt.h"

idt_entry_t idt[IDT_ENTRIES];
idt_ptr_t   idt_ptr;

extern void idt_load(uint32_t);

void idt_init()
{
    idt_ptr.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;
    idt_ptr.base  = (uint32_t)&idt;

    for(int i = 0; i < IDT_ENTRIES; i++)
    {
        idt[i].offset_low  = 0;
        idt[i].selector    = 0x08;
        idt[i].zero        = 0;
        idt[i].type_attr   = 0x8E;
        idt[i].offset_high = 0;
    }

    idt_load((uint32_t)&idt_ptr);
}