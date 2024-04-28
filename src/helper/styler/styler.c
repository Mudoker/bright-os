#include "./styler.h"
#include "../../global/global.h"
#include "../../uart/uart.h"
#include "../utils/utils.h"

// Function to format string with color and print it
void str_format(const char *str, const char *color_code,
                const char *bg_color_code) {

  // Check if the input is valid or not (not null)
  if (str == (char *)0 || color_code == (char *)0 ||
      bg_color_code == (char *)0) {
    return; // Invalid input
  }

  // Initialize the formatted string
  static char formatted_str[MAX_STR_LEN];

  // Initialize the string
  formatted_str[0] = '\0';

  // Concatenate strings
  concat(formatted_str, color_code);    // Add color code
  concat(formatted_str, bg_color_code); // Add background color code
  concat(formatted_str, str);           // Add the string

  uart_puts(formatted_str); // Print the formatted string
}

// Print text in box
void print_in_box(char *str) {
  // Print the formatted string in a box
  uart_puts("\n");

  // Print the box corners
  str_format("+", THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);

  // Print dashes
  for (int i = 0; i < len(str) + 2; i++) {
    str_format("-", THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  }

  // Print the box corners
  str_format("+", THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);

  uart_puts("\n");

  // Print the box sides
  str_format("| ", THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(str, THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(" |", THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);

  uart_puts("\n");

  // Print the box corners
  str_format("+", THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);

  // Print dashes
  for (int i = 0; i < len(str) + 2; i++) {
    str_format("-", THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  }

  // Print the box corners
  str_format("+", THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  uart_puts("\n");
}

// Tabulate keys and values
void tabulate(char *keys[], int numKeys, char *values[][MAX_ROWS],
              int numValues) {

  // Initialize the maximum length of each column
  int maxColLength[MAX_COLS] = {8};

  // Calculate the maximum length of each column
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
    // Print keys for current row
    str_format(keys[i], THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);

    // Adjust spacing based on the maximum length of the column
    for (int j = 0; j < maxColLength[i] - len(keys[i]) + 12;
         j++) { // Added 4 spaces for padding
      uart_puts(" ");
    }
  }

  uart_puts("\n\n");

  // Print values
  for (int i = 0; i < numValues; i++) {
    // Format values based on the key
    // If the key is "Parity" or "Handshake", format the values
    if (is_equal(values[i][0], "Parity")) {
      // Convert the values from 0, 1, 2 to None, Odd, Even
      if (is_equal(values[i][1], "0")) {
        values[i][1] = "None";
      } else if (is_equal(values[i][1], "1")) {
        values[i][1] = "Odd";
      } else if (is_equal(values[i][1], "2")) {
        values[i][1] = "Even";
      }
    } else if (is_equal(values[i][0], "Handshake")) {
      // Convert the values from 0, 1 to None and RTS/CTS
      if (is_equal(values[i][1], "0")) {
        values[i][1] = "None";
      } else if (is_equal(values[i][1], "1")) {
        values[i][1] = "RTS/CTS";
      } else {
        values[i][1] = "Invalid";
      }
    }
    // Print values for current row
    for (int j = 0; j < numKeys && values[i][j] != (char *)0; j++) {
      str_format(values[i][j], THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);

      // Adjust spacing based on the maximum length of the column
      for (int k = 0; k < maxColLength[j] - len(values[i][j]) + 12;
           k++) { // Added 4 spaces for padding
        uart_puts(" ");
      }
    }

    uart_puts("\n");
  }
}
