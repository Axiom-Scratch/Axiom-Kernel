#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_COLOR 0x0F

void kernel_main()
{
    uint16_t* video = (uint16_t*)0xB8000;

    // clear screen
    for(int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        video[i] = (VGA_COLOR << 8) | ' ';
    }

    const char* msg = "Hello Kernel, Welcome to Axiom-Kernel";

    for(int i = 0; msg[i] != 0; i++)
    {
        video[i] = (VGA_COLOR << 8) | msg[i];
    }

    while(1) {}
}