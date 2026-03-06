#include <stdint.h>

void kernel_main()
{
    char* video = (char*)0xB8000;

    // clear screen
    for(int i = 0; i < 80*25; i++)
    {
        video[i*2] = ' ';
        video[i*2+1] = 0x0F;
    }

    const char* msg = "Hello Kernel, Welcome to Axiom-Kernel";

    for(int i = 0; msg[i] != 0; i++)
    {
        video[i*2] = msg[i];
        video[i*2+1] = 0x0F;
    }

    while(1) {}
}