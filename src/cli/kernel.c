#include "./kernel.h"

// Clear the current command and show the prompt
void clear_current_command() {
  // ANSI escape code to clear the current line
  uart_puts("\033[2K\r");

  // Show prompt
  str_format("BrightOS> ", THEME.PRIMARY_COLOR);
}

// CLI function to get the command from the user
void cli() {
  static char cli_buffer[MAX_CMD_SIZE] = {0}; // Buffer to store the command
  static int index = 0;          // Index to keep track of the buffer
  static int is_new_command = 1; // Flag to check if a new command is entered
  static CommandStack command_stack = {.top_index = -1}; // History stack
  static int history_index = -1; // Index to keep track of command history
  static int was_down = 0; // Check if the current move up after a move down

  // Show prompt only if new command
  if (is_new_command) {
    // Clear the buffer
    for (int i = 0; i < MAX_CMD_SIZE; i++) {
      cli_buffer[i] = '\0';
    }

    // Wait until the TX FIFO is empty
    while (!(UART0_FR & UART0_FR_TXFE)) {
      // Wait until the TX FIFO is empty
    }

    str_format("BrightOS> ", THEME.PRIMARY_COLOR);

    is_new_command = 0;
    history_index = -1;
  }

  // Check if UART configuration is needed
  if (IS_REINIT_UART) {
    /* The reason for this is that the UART re-configuration is triggered by the
     * user input. When the configuration is about setting the baud rate, due to
     * mismatch baud rate on the terminal, the user input is not captured
     * correctly. To fix this, an additional empty character is added to the
     * buffer to trigger the UART configuration. */
    str_format(" ", THEME.PRIMARY_COLOR);

    // Wait until the TX FIFO is empty
    while (!(UART0_FR & UART0_FR_TXFE)) {
      // Wait until the TX FIFO is empty
    }

    // Reinitialize UART
    uart_init();
    IS_REINIT_UART = 0;
  }

  // Get command from user
  char c = uart_getc();
  if (c == '\b') {
    // Prevent deleting the prompt
    if (index > 0) {
      // Update the buffer and index
      index--;
      cli_buffer[index] = '\0';

      // Move the cursor back, print a space, and move the cursor back again
      uart_puts("\b \b");
    }
  } else if (c == '\t') { // Tab key pressed
    // Autocomplete command
    char *completed_command = autocomplete_command(cli_buffer);

    // If a command is completed, update the buffer and index
    if (completed_command != (char *)0) {
      // Clear the current command
      clear_current_command();

      // Copy the completed command to the buffer
      copy(cli_buffer, completed_command);

      // Move the cursor to the end of the buffer
      index = len(cli_buffer);

      // Print the completed command
      uart_puts(cli_buffer);
    }
  } else if (c == '+' || c == '_') {
    /*
    Set the history index to the top index if it is -1 (no command entered or
    haven't navigated history)
    */
    if (history_index == -1)
      history_index = command_stack.top_index;

    // Move backward in history (towards older commands)
    if (c == '_' && history_index >= 0) {
      clear_current_command();

      // If was_down is true, then the current command is already in the buffer
      if (was_down) {
        // If the history index is at the top, then set the buffer to empty
        history_index = (history_index == 0) ? 0 : history_index - 1;
        copy(cli_buffer, command_stack.command[history_index]);
      } else {
        // Copy the current command to the buffer
        copy(cli_buffer, command_stack.command[history_index]);
        history_index = (history_index == 0) ? 0 : history_index - 1;
      }

      // Move the cursor to the end of the buffer
      index = len(cli_buffer);
      str_format(cli_buffer, THEME.SECONDARY_COLOR); // Print the command
    } else if (c == '+' && history_index <= command_stack.top_index) {
      // Set the flag to true as this is a move down
      was_down = 1;

      // Move forward in history (towards newer commands)
      clear_current_command();

      history_index++;

      // If the history index is at the top, then add an empty buffer, allowing
      // user to enter a new command
      if (history_index > command_stack.top_index) {
        copy(cli_buffer, "");
      } else {
        copy(cli_buffer, command_stack.command[history_index]);
      }

      // Move the cursor to the end of the buffer
      index = len(cli_buffer);

      // Print the command
      str_format(cli_buffer, THEME.SECONDARY_COLOR);
    }
  } else {
    // Get the command until newline
    if (c != '\n') {
      // Append the character to the buffer
      if (index < MAX_CMD_SIZE - 1) {
        cli_buffer[index] = c;
        index++;

        // Convert character to string and print
        char str[2] = {c, '\0'};
        str_format(str, THEME.SECONDARY_COLOR);
      } else {
        str_format("Command too long\n", THEME.ERROR_COLOR);
        index = 0;
        is_new_command = 1;
      }
    } else {
      // Reset the flag
      was_down = 0;

      // Add null terminator to the buffer
      cli_buffer[index] = '\0';

      // Push the command to the history stack
      push_command(&command_stack, cli_buffer);

      // Parse the command from the buffer and execute
      parse_command(cli_buffer);

      // Handle special commands: Show history of previous commands
      if (is_equal(cli_buffer, "hist")) {
        print_in_box("Command History");
        get_all_commands(&command_stack);
      }

      // Reset the buffer
      uart_puts("\n");

      // Reset the flag and index
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
    // Embed the background color
    uart_puts(THEME.BACKGROUND_COLOR);

    // Start the CLI
    cli();
  }

  return 0;
}
