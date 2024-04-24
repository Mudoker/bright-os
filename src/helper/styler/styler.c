#include "./styler.h"
#include "../../global/global.h"
#include "../../uart/uart.h"
#include "../utils/utils.h"

// Function to format string with color and print it
void str_format(char *str, const char *color_code) {
  if (str == (char *)0 || color_code == (char *)0) {
    return; // Invalid input
  }

  static char formatted_str[MAX_STR_LEN];

  formatted_str[0] = '\0'; // Initialize the string

  // Concatenate the style code, color code and the string
  concat(formatted_str, color_code);
  concat(formatted_str, str);
  concat(formatted_str, "\033[0m \0");

  uart_puts(formatted_str);
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

void tabulate(char *keys[], int numKeys, char *values[][MAX_ROWS],
              int numValues) {

  int maxColLength[MAX_COLS] = {8}; // Initialize all lengths to 8
  for (int i = 0; i < numValues; i++) {
    for (int j = 0; j < numKeys && values[i][j] != (char *)0; j++) {
      int colLen = len(values[i][j]);
      if (colLen > maxColLength[j]) {
        maxColLength[j] = colLen;
      }
    }
  }

  // Print keys
  for (int i = 0; i < numKeys; i++) {
    str_format(keys[i], OS_CONFIG.PRIMARY_COLOR);
    // Adjust spacing based on the maximum length of the column
    for (int j = 0; j < maxColLength[i] - len(keys[i]) + 4;
         j++) { // Added 4 spaces for padding
      uart_puts(" ");
    }
  }
  uart_puts("\n\n");

  // Print values
  for (int i = 0; i < numValues; i++) {
    // Print values for current row
    for (int j = 0; j < numKeys && values[i][j] != (char *)0; j++) {
      str_format(values[i][j], OS_CONFIG.SECONDARY_COLOR);
      // Adjust spacing based on the maximum length of the column
      for (int k = 0; k < maxColLength[j] - len(values[i][j]) + 4;
           k++) { // Added 4 spaces for padding
        uart_puts(" ");
      }
    }
    uart_puts("\n");
  }
}