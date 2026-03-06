# Axiom-Kernel
Axiom-Kernel

# Minimal Kernel

Tiny **x86 hobby kernel** for learning OS development.

## Structure

boot/grub/grub.cfg
src/boot.asm
src/kernel.c
linker.ld
build.sh


## Build
```bash
./build.sh
Run
qemu-system-i386 -cdrom kernel.iso

Output:

Hello Kernel, Welcome to Axiom-Kernel