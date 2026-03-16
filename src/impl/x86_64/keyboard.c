#include "print.h"
#include "terminal.h"
#include <stdint.h>

/* =========================
   Port I/O helpers
   ========================= */

static inline uint8_t inb(uint16_t port) {
  uint8_t value;
  __asm__ volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
  return value;
}

static inline void outb(uint16_t port, uint8_t value) {
  __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

/* =========================
   Keyboard scancode map
   ========================= */

static const char keyboard_map[128] = {
    0,   27,  '1',  '2',  '3',  '4', '5', '6',  '7', '8', '9', '0',
    '-', '=', '\b', '\t', 'q',  'w', 'e', 'r',  't', 'y', 'u', 'i',
    'o', 'p', '[',  ']',  '\n', 0,   'a', 's',  'd', 'f', 'g', 'h',
    'j', 'k', 'l',  ';',  '\'', '`', 0,   '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm',  ',',  '.',  '/', 0,   '*',  0,   ' ',
};

/* =========================
   Keyboard interrupt handler
   ========================= */

void isr33_handler() {
  uint8_t scancode = inb(0x60);

  /* Ignore key releases */
  if (scancode & 0x80) {
    outb(0x20, 0x20);
    return;
  }

  char c = keyboard_map[scancode];

  if (c)
    terminal_putchar(c);

  /* Send End Of Interrupt to PIC */
  outb(0x20, 0x20);
}
