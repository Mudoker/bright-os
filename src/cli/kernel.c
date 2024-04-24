#include "../commands/os.h"
#include "../global/global.h"
#include "../helper/styler/styler.h"
#include "../helper/utils/utils.h"
#include "../uart/uart.h"

void clear_current_command() {
  // Clear the current command
  uart_puts("\033[2K\r");

  // Show prompt
  str_format("BrightOS> ", OS_CONFIG.PRIMARY_COLOR);
}

void cli() {
  static char cli_buffer[MAX_CMD_SIZE] = {0};
  static int index = 0;
  static int is_new_command = 1;
  static CommandStack command_stack = {.top_index = -1};
  static int history_index = -1;
  static int was_down = 0;

  // Show prompt only if new command
  if (is_new_command) {
    for (int i = 0; i < MAX_CMD_SIZE; i++) {
      cli_buffer[i] = '\0';
    }
    uart_puts("\n");
    str_format("BrightOS> ", OS_CONFIG.PRIMARY_COLOR);
    is_new_command = 0;
    history_index = -1;
  }

  // Get command from user
  char c = uart_getc();
  if (c == '\b') {
    // Prevent deleting the prompt
    if (index > 0) {
      // Update the buffer and index
      index--;
      cli_buffer[index] = '\0';
      uart_puts("\b \b");
    }
  } else if (c == '\t') { // Tab key pressed
    // Autocomplete command
    char *completed_command = autocomplete_command(cli_buffer);
    if (completed_command != (char *)0) {
      clear_current_command();
      copy(cli_buffer, completed_command);
      index = len(cli_buffer);
      uart_puts(cli_buffer);
    }
  } else if (c == '+' || c == '_') {
    if (history_index == -1)
      history_index = command_stack.top_index;

    // Navigate command history
    if (c == '+' && history_index >= 0) {
      clear_current_command();

      if (was_down) {
        history_index = (history_index == 0) ? 0 : history_index - 1;
        copy(cli_buffer, command_stack.command[history_index]);
      } else {
        copy(cli_buffer, command_stack.command[history_index]);
        history_index = (history_index == 0) ? 0 : history_index - 1;
      }

      index = len(cli_buffer);
      uart_puts(cli_buffer);

    } else if (c == '_' && history_index <= command_stack.top_index) {
      was_down = 1;

      // Move forward in history (towards older commands)
      clear_current_command();

      history_index = (history_index == command_stack.top_index)
                          ? command_stack.top_index
                          : history_index + 1;

      copy(cli_buffer, command_stack.command[history_index]);
      index = len(cli_buffer);
      uart_puts(cli_buffer);
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
      was_down = 0;
      // Add null terminator to the buffer
      cli_buffer[index] = '\0';
      push_command(&command_stack, cli_buffer);

      parse_command(cli_buffer);

      if (is_equal(cli_buffer, "hist")) {
        uart_puts("\n");
        get_all_commands(&command_stack);
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
  //   os_greet();

  // OS loop
  while (1) {
    cli();
  }

  return 0;
}
