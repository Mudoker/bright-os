#include "./styler.h"
#include "../../global/global.h"
#include "../../uart/uart.h"
#include "../utils/utils.h"

// Function to format string with color and print it
void str_format(char *str, const char *color_code, const char *bg_color_code) {
  if (str == (char *)0 || color_code == (char *)0 ||
      bg_color_code == (char *)0) {
    return; // Invalid input
  }

  static char formatted_str[MAX_STR_LEN];

  formatted_str[0] = '\0'; // Initialize the string

  // Concatenate strings
  concat(formatted_str, color_code);
  concat(formatted_str, bg_color_code);
  concat(formatted_str, str);

  uart_puts(formatted_str);
}

// Print text in box
void print_in_box(char *str) {
  // Print the formatted string in a box
  uart_puts("\n");
  str_format("+", OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  for (int i = 0; i < len(str) + 2; i++) {
    str_format("-", OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  }
  str_format("+", OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  str_format("| ", OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  str_format(str, OS_CONFIG.PRIMARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  str_format(" |", OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  str_format("+", OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  for (int i = 0; i < len(str) + 2; i++) {
    str_format("-", OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  }
  str_format("+", OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");
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
    str_format(keys[i], OS_CONFIG.PRIMARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
    // Adjust spacing based on the maximum length of the column
    for (int j = 0; j < maxColLength[i] - len(keys[i]) + 4;
         j++) { // Added 4 spaces for padding
      uart_puts(" ");
    }
  }

  uart_puts("\n\n");

  // Print values
  for (int i = 0; i < numValues; i++) {
    if (is_equal(values[i][0], "Parity")) {
      if (is_equal(values[i][1], "0")) {
        values[i][1] = "None";
      } else if (is_equal(values[i][1], "1")) {
        values[i][1] = "Odd";
      } else if (is_equal(values[i][1], "2")) {
        values[i][1] = "Even";
      }
    } else if (is_equal(values[i][0], "Handshake")) {
      if (is_equal(values[i][1], "0")) {
        values[i][1] = "None";
      } else if (is_equal(values[i][1], "1")) {
        values[i][1] = "RTS/CTS";
      } else if (is_equal(values[i][1], "2")) {
        values[i][1] = "Invalid";
      }
    }
    // Print values for current row
    for (int j = 0; j < numKeys && values[i][j] != (char *)0; j++) {
      str_format(values[i][j], OS_CONFIG.SECONDARY_COLOR,
                 OS_CONFIG.BACKGROUND_COLOR);

      // Adjust spacing based on the maximum length of the column
      for (int k = 0; k < maxColLength[j] - len(values[i][j]) + 4;
           k++) { // Added 4 spaces for padding
        uart_puts(" ");
      }
    }
    uart_puts("\n");
  }
}
