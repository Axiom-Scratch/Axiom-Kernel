#include "print.h"
#include <stddef.h>
#include <stdint.h>

#define VGA_MEMORY 0xB8000

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

struct Char {
  uint8_t character;
  uint8_t color;
};

static volatile struct Char *buffer = (struct Char *)VGA_MEMORY;
static size_t col = 0;
static size_t row = 0;

static uint8_t color = PRINT_COLOR_WHITE | (PRINT_COLOR_BLACK << 4);

static inline size_t vga_index(size_t x, size_t y) { return y * VGA_WIDTH + x; }

static inline void outb(uint16_t port, uint8_t value) {
  __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline void vga_update_cursor(size_t x, size_t y) {
  uint16_t pos = y * VGA_WIDTH + x;

  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint8_t)(pos & 0xFF));

  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void clear_row(size_t row) {
  struct Char empty = {
      .character = ' ',
      .color = color,
  };

  for (size_t c = 0; c < VGA_WIDTH; c++) {
    buffer[vga_index(c, row)] = empty;
  }
}

void print_clear() {
  for (size_t r = 0; r < VGA_HEIGHT; r++) {
    clear_row(r);
  }
  col = 0;
  row = 0;
  vga_update_cursor(col, row);
}

void print_newline() {
  col = 0;

  if (row < VGA_HEIGHT - 1) {
    row++;
    vga_update_cursor(col, row);
    return;
  }

  for (size_t r = 1; r < VGA_HEIGHT; r++) {
    for (size_t c = 0; c < VGA_WIDTH; c++) {
      buffer[c + VGA_WIDTH * (r - 1)] = buffer[c + VGA_WIDTH * r];
    }
  }

  clear_row(VGA_HEIGHT - 1);
  vga_update_cursor(col, row);
}

void print_char(char character) {
  if (character == '\n') {
    print_newline();
    return;
  }

  if (col >= VGA_WIDTH) {
    print_newline();
  }

  buffer[vga_index(col, row)] = (struct Char){
      .character = (uint8_t)character,
      .color = color,
  };

  col++;
  vga_update_cursor(col, row);
}

void print_str(const char *str) {
  for (size_t i = 0; str[i] != '\0'; i++) {
    print_char(str[i]);
  }
}

void print_set_color(uint8_t foreground, uint8_t background) {
  color = foreground | (background << 4);
}
