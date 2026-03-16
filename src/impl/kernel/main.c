#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "print.h"
#include "terminal.h"

void kernel_main() {
  print_clear();
  idt_init();
  pic_remap();
  pit_init(100);

  __asm__ volatile("sti");

  print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
  print_str("AxiomOS 1.0v\n");
  terminal_init();

  // print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
  // print_str("HI Layton\n");
  // print_set_color(PRINT_COLOR_BLUE, PRINT_COLOR_BLACK);
  // print_str("HOW IS ARCH LINUX GOING ON!\n");
  // print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
  // print_str("AND ALSO HOW DEVVING GOING ON? :)\n");
  // print_str("HAHAHAH\n");

  print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);

  while (1)
    __asm__ volatile("hlt");
}
