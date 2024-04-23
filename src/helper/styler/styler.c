#include "./styler.h"
#include "../../global/global.h"
#include "../../uart/uart.h"
#include "../utils/utils.h"

// Function to format string with color and print it
char *str_format(char *str, const char *color_code, int style) {
  if (str == (char *)0 || color_code == (char *)0) {
    return (char *)0; // Invalid input
  }

  char *style_code = "";

  // Assign style code based on bold and italic flags
  if (style == 111) {
    concat(style_code, STYLER.BOLD_ON);
    concat(style_code, STYLER.ITALIC_ON);
    concat(style_code, STYLER.UNDERLINE_ON);
  } else if (style == 1) {
    style_code = STYLER.BOLD_ON;
  } else if (style == 10) {
    style_code = STYLER.ITALIC_ON;
  } else if (style == 100) {
    style_code = STYLER.UNDERLINE_ON;
  }

  static char formatted_str[MAX_STR_LEN];

  formatted_str[0] = '\0';

  // Concatenate the style code, color code and the string
  concat(formatted_str, style_code);
  concat(formatted_str, color_code);
  concat(formatted_str, str);
  concat(formatted_str, "\033[0m");

  formatted_str[len(formatted_str)] = '\0';

  return formatted_str;
}

// Print text in box
void print_in_box(char *str) {
  // Print the formatted string in a box
  uart_puts("\n");
  uart_puts("+");
  for (int i = 0; i < len(str) + 2; i++) {
    uart_puts("-");
  }
  uart_puts("+\n");

  uart_puts("| ");
  uart_puts(str);
  uart_puts(" |\n");

  uart_puts("+");
  for (int i = 0; i < len(str) + 2; i++) {
    uart_puts("-");
  }
  uart_puts("+\n");
}