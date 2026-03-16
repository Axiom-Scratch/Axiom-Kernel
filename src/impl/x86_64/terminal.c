#include "terminal.h"
#include "print.h"

#define INPUT_BUFFER_SIZE 256

static char input_buffer[INPUT_BUFFER_SIZE];
static int input_pos = 0;

/* -------------------------
   Minimal strcmp
------------------------- */
static int strcmp(const char *a, const char *b) {
  while (*a && *b) {
    if (*a != *b)
      return *a - *b;

    a++;
    b++;
  }
  return *a - *b;
}

/* -------------------------
   Terminal prompt
------------------------- */
static void terminal_prompt() {
  print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
  print_str("> ");
  print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
}

/* -------------------------
   Initialize terminal
------------------------- */
void terminal_init() { terminal_prompt(); }

/* -------------------------
   Execute command
------------------------- */
static void terminal_execute() {

  print_char('\n');

  if (input_pos == 0) {
    terminal_prompt();
    return;
  }

  input_buffer[input_pos] = 0;

  if (!strcmp(input_buffer, "help")) {

    print_set_color(PRINT_COLOR_BLUE, PRINT_COLOR_BLACK);
    print_str("Commands: help clear\n");

  } else if (!strcmp(input_buffer, "clear")) {

    print_clear();

  } else {

    print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLACK);
    print_str("Unknown command\n");
  }

  input_pos = 0;

  terminal_prompt();
}

/* -------------------------
   Handle typed characters
------------------------- */
void terminal_putchar(char c) {

  /* ENTER */
  if (c == '\n') {
    terminal_execute();
    return;
  }

  /* BACKSPACE */
  if (c == '\b') {
    if (input_pos > 0) {
      input_pos--;
      print_char('\b');
      print_char(' ');
      print_char('\b');
    }
    return;
  }

  /* Prevent buffer overflow */
  if (input_pos >= INPUT_BUFFER_SIZE - 1)
    return;

  input_buffer[input_pos++] = c;

  print_char(c);
}
