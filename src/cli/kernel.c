#include "../commands/os.h"
#include "../global/global.h"
#include "../helper/styler/styler.h"
#include "../helper/utils/utils.h"
#include "../uart/uart.h"

void cli() {
  static char cli_buffer[MAX_CMD_SIZE] = {0};
  static int index = 0;
  static int is_new_command = 1;

  // Show prompt only if new command
  char *prompt = str_format("BrightOS> ", COLOR.YELLOW, 0);
  if (is_new_command) {
    uart_puts("\n");
    uart_puts(prompt);
    is_new_command = 0;
  }

  // Get command from user
  char c = uart_getc();

  // Check for backspace
  if (c == '\b') {
    // Prevent backspace from deleting the prompt
    if (index > 0) {
      // Update the buffer and index
      index--;
      cli_buffer[index] = '\0';
      uart_puts("\b \b");
    }
  } else {
    // Get the command until newline
    if (c != '\n') {
      // Append the character to the buffer
      if (index < MAX_CMD_SIZE - 1) {
        cli_buffer[index] = c;
        index++;
        uart_sendc(c);
      } else {
        uart_puts("\nCommand too long. Please try again.\n");
        index = 0;
        is_new_command = 1;
      }
    } else {
      // Add null terminator to the buffer
      cli_buffer[index] = '\0';

      // Compare and execute the command
      if (is_equal(cli_buffer, "os") == 0) {
        os_greet();
      } else if (is_equal(cli_buffer, "clr") == 0 ||
                 is_equal(cli_buffer, "cls") == 0 ||
                 is_equal(cli_buffer, "clear") == 0) {
        uart_puts("\033c"); // Full terminal reset
      } else {
        uart_puts("\nInvalid command. Type 'help' to see available commands.");
      }

      // Reset the buffer
      uart_puts("\n");
      index = 0;
      is_new_command = 1;
    }
  }
}

int main() {
  // set up serial console
  uart_init();

  // Welcome message
  os_greet();

  // OS loop
  while (1) {
    cli();
  }

  return 0;
}
