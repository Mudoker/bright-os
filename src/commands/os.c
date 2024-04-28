#include "os.h"
#include "../cli/kernel.h"
#include "../global/global.h"
#include "../helper/styler/styler.h"
#include "../helper/utils/utils.h"
#include "../mbox/mbox.h"

char *commands[] = {"os",       "help", "help <name>", "clear",  "hist",
                    "setcolor", "ref",  "showinfo",    (char *)0};

char *extended_commands[] = {"help setcolor", "help ref",  "help showinfo",
                             "help clear",    "help hist", "help os",
                             "help help",     "ref -uart", (char *)0};

void os_greet() {
  uart_puts("\n");

  // Print OS logo
  str_format(OS_INFO.ASCII_ART_LOGO, THEME.PRIMARY_COLOR,
             THEME.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print OS Information box
  print_in_box("OS Information");
  uart_puts("\n");

  // Format and print "ID" title
  str_format("ID           : ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(OS_INFO.OS_ID, THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  uart_puts("\n");

  // Format and print "OS Name" title
  str_format("OS Name      : ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(OS_INFO.OS_NAME, THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  uart_puts("\n");

  // Format and print "Version" title
  str_format("Version      : ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(OS_INFO.OS_VERSION, THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  uart_puts("\n");

  // Author Information
  print_in_box("Author Information");
  uart_puts("\n");

  // Print author name
  str_format("Author       : ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(OS_INFO.AUTHOR_NAME, THEME.SECONDARY_COLOR,
             THEME.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print author username
  str_format("Username     : ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(OS_INFO.AUTHOR_USERNAME, THEME.SECONDARY_COLOR,
             THEME.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print author SID
  str_format("SID          : ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(OS_INFO.AUTHOR_SID, THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print author email
  str_format("Email        : ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(OS_INFO.AUTHOR_EMAIL, THEME.SECONDARY_COLOR,
             THEME.BACKGROUND_COLOR);

  // Print author github
  str_format("Github       : ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);

  str_format(OS_INFO.AUTHOR_GITHUB_URL, THEME.SECONDARY_COLOR,
             THEME.BACKGROUND_COLOR);

  uart_puts("\n");

  // Copyright
  print_in_box("Acknowledgement");
  uart_puts("\n");

  // Print school name (RMIT SSET)
  str_format("School       : ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(OS_INFO.ACK_SCHOOL, THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print course name (Embedded Systems 3)
  str_format("Course       : ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(OS_INFO.ACK_COURSE, THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print lecturer name (Mr. Linh T.D.)
  str_format("Lecturer     : ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(OS_INFO.ACK_LECTURER, THEME.SECONDARY_COLOR,
             THEME.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print submitted by
  str_format("Submitted by : ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(OS_INFO.ACK_SUBMITTED_BY, THEME.SECONDARY_COLOR,
             THEME.BACKGROUND_COLOR);
  uart_puts("\n\n");

  // Print declaration
  str_format(OS_INFO.ACK_DECLARATION, THEME.SECONDARY_COLOR,
             THEME.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print OS logo
  str_format(OS_INFO.ASCII_ART_LOGO_TEXT, THEME.PRIMARY_COLOR,
             THEME.BACKGROUND_COLOR);
  uart_puts("\n");

  str_format("@2024. All rights reserved.", THEME.SECONDARY_COLOR,
             THEME.BACKGROUND_COLOR);
  uart_puts("\n\n");
}

// As per limitations of bare-metal programming, the stack is implemented as
// using a fixed-size array
// Command stack methods
void push_command(struct CommandStack *stack, char *command) {
  // Check if the stack is full
  if (stack->top_index == MAX_CMD_HISTORY - 1) {
    // Shift the stack to the left
    for (int i = 0; i < MAX_CMD_HISTORY - 1; i++) {
    }
  } else {
    // Increment the top index
    stack->top_index++;
  }

  // Copy the command to the top of the stack
  copy(stack->command[stack->top_index], command);
}

void pop_command(struct CommandStack *self) {
  // Check if the stack is empty
  if (self->top_index == -1) {
    return;
  }

  // Decrement the top index
  self->top_index--;
}

void get_command(struct CommandStack *self) {
  // Check if the stack is empty
  if (self->top_index == -1) {
    return;
  }

  // Get the command at the top of the stack
  uart_puts(self->command[self->top_index]);
}

void get_all_commands(struct CommandStack *stack) {
  // Check if the stack is empty
  if (stack->top_index == -1) {
    return;
  }

  // Print all commands in the stack
  for (int i = 0; i <= stack->top_index; i++) {
    uart_puts(stack->command[i]);
    uart_puts("\n");
  }
}

void initialize_values(char *values[MAX_ROWS][MAX_ROWS], int rows) {
  for (int i = 0; i < MAX_ROWS; i++) {
    for (int j = 0; j < rows; j++) {
      values[i][j] = (char *)0;
    }
  }
}

void show_help(char *command) {
  char *keys[] = {"Command", "Description"};
  char *values[MAX_ROWS][MAX_ROWS];
  char *commands_desc[MAX_ROWS][MAX_ROWS];

  // Ref: Help command on Linuxcommand
  str_format("\n\nBrightOS, Version 1.0\n", THEME.SECONDARY_COLOR,
             THEME.BACKGROUND_COLOR);
  str_format("These shell commands are defined internally. Type 'help' to see "
             "this list.\n",
             THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format("Type 'help name' to find out more about the function 'name'.\n",
             THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format("A star (*) next to a name means that the command is disabled.\n",
             THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);

  initialize_values(values, 9);        // Initialize the values array
  initialize_values(commands_desc, 9); // Initialize the commands_desc array

  commands_desc[0][0] = "Show OS information\n";
  commands_desc[1][0] = "Show all commands\n";
  commands_desc[2][0] = "Show help for a command\n";
  commands_desc[3][0] = "Clear the terminal\n";
  commands_desc[4][0] = "Show command history\n";
  commands_desc[5][0] = "Change color of OS";
  commands_desc[5][1] =
      "-[target]: b: background, t: text, os: os theme, "
      "pri: primary, sec: secondary, err: ERROR_COLOR, suc: SUCCESS_COLOR\n";
  commands_desc[5][2] =
      "-[color]: red, green, yellow, blue, purple, cyan, white, "
      "black, bright (os only), dark (os only), light (os only)";
  commands_desc[5][3] =
      "\nE.g.: setcolor -t red -b yellow -pri green -sec cyan";
  commands_desc[6][0] = "Show reference for a target\n";
  commands_desc[6][1] = "-[target]: uart";
  commands_desc[6][2] =
      "-baud [value]: set baud rate (Allowed values: 300,600, 1200, 2400, "
      "4800, 9600,14400, 19200, 38400, 57600, 115200, 230400, 460800, "
      "921600)\n";
  commands_desc[6][3] =
      "-dbits [value]: set data bits (Allowed values: 5, 6, 7, "
      "8)\n";
  commands_desc[6][4] =
      "-sbits [value]: set stop bits (Allowed values: 1, 2)\n";
  commands_desc[6][5] =
      "-par [value]: set parity (Allowed values: none, even, odd)\n";
  commands_desc[6][6] = "-handshake [value]: set handshake (Allowed values: 0: "
                        "none, 1: CTS/RTS)\n";
  commands_desc[6][7] = "\nE.g.: ref -uart -baud 115200 -dbits 8 -sbits 1 -par "
                        "none -c -handshake 1";
  commands_desc[7][0] = "Show current device information\n";
  commands_desc[7][1] = "-v: show full informationlk";
  commands_desc[7][2] = "\nE.g.: showinfo -v";
  commands_desc[8][0] = (char *)0;

  // Display help menu
  uart_puts("\n");

  // Display commands in tabular format
  int num_rows = 0;
  if (is_equal(command, "all")) {
    for (int i = 0; commands[i] != (char *)0; i++) {
      values[i][0] = commands[i];
      num_rows++;
    }

    for (int i = 0; commands_desc[i][0] != (char *)0; i++) {
      values[i][1] = commands_desc[i][0];
    }
  } else {
    // Display help for a specific command
    int i;
    for (i = 0; commands[i] != (char *)0; i++) {
      if (is_equal(command, commands[i])) {
        values[0][0] = commands[i];
        values[0][1] = commands_desc[i][0];
        num_rows++;
        for (int j = 1; commands_desc[i][j] != (char *)0; j++) {
          values[j][0] = "";
          values[j][1] = commands_desc[i][j];
          num_rows++;
        }
        break;
      }
    }
    if (commands[i] == (char *)0) {
      str_format(
          "\n\nCommand not found. Type 'help' to see available commands.\n",
          THEME.ERROR_COLOR, THEME.BACKGROUND_COLOR);
      return;
    }
  }

  tabulate(keys, 2, values, num_rows);
}

// Auto-complete command
char *autocomplete_command(char *buffer) {
  if (len(buffer) == 0) {
    return (char *)0;
  }

  for (int i = 0; commands[i] != (char *)0; i++) {
    if (starts_with(commands[i], buffer)) {
      return commands[i];
    }
  }

  for (int i = 0; extended_commands[i] != (char *)0; i++) {
    if (starts_with(extended_commands[i], buffer)) {
      return extended_commands[i];
    }
  }

  return (char *)0;
}

// Show command execution status
void show_status(int status, char *msg) {
  const char *color;

  if (status == 0) {
    color = THEME.SUCCESS_COLOR;
  } else {
    color = THEME.ERROR_COLOR;
  }

  str_format("\n\n", THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
  str_format(msg, color, THEME.BACKGROUND_COLOR);
  str_format("\n", THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);
}

// Parse flags from the input
int parse_flags(char *input, char *flags[], int max_flags, int min_flags) {
  int i = 0;
  int j = 0;
  int k = 0;
  int flag_count = 0;
  char flag_buffer[MAX_CMD_SIZE][MAX_CMD_SIZE];

  for (int i = 0; i < MAX_CMD_SIZE; i++) {
    for (int j = 0; j < MAX_CMD_SIZE; j++) {
      flag_buffer[i][j] = '\0';
    }
  }

  while (input[i] != '\0' && k < MAX_CMD_SIZE) {
    if (input[i] == '-') {
      i++;
      j = 0; // Reset j for a new flag
      flag_count++;

      while (input[i] != '\0' && input[i + 1] != '-' && j < MAX_CMD_SIZE - 1) {
        flag_buffer[k][j++] = input[i++];
      }

      flag_buffer[k][j] = '\0';  // Null-terminate the flag string
      flags[k] = flag_buffer[k]; // Store the flag in the flags array
      k++;                       // Increment index for the flags array
    }
    i++;
  }

  // Check if the number of flags exceeds the maximum allowed flags
  if (flag_count > max_flags) {
    str_format(
        "\n\nToo many flags. Type 'help <command>' to see available flags.\n",
        THEME.ERROR_COLOR, THEME.BACKGROUND_COLOR);
    return False;
  }

  // Check if the number of flags is less than the minimum required flags
  if (flag_count < min_flags) {
    str_format(
        "\n\nToo few flags. Type 'help <command>' to see available flags.\n",
        THEME.ERROR_COLOR, THEME.BACKGROUND_COLOR);
    return False;
  }
  return flag_count;
}

// Parse target from the flags
void parse_target(char *flag, char *target, char *option) {
  // Extract the target and option
  int k = 0;
  while (flag[k] != '\0' && flag[k] != ' ') {
    target[k] = flag[k];
    k++;
  }

  target[k] = '\0'; // Null-terminate the target

  // Skip spaces after target
  while (flag[k] == ' ') {
    k++;
  }

  // Extract the option
  int l = 0;
  while (flag[k] != '\0') {
    option[l++] = flag[k++];
  }

  option[l] = '\0'; // Null-terminate the option
}

// Parse the color from the flags
char *to_color(char *flag, int type) {
  if (type == 0) {
    if (is_equal(flag, "red"))
      return COLOR.RED;
    else if (is_equal(flag, "green"))
      return COLOR.GREEN;
    else if (is_equal(flag, "yellow"))
      return COLOR.YELLOW;
    else if (is_equal(flag, "blue"))
      return COLOR.BLUE;
    else if (is_equal(flag, "purple"))
      return COLOR.PURPLE;
    else if (is_equal(flag, "cyan"))
      return COLOR.CYAN;
    else if (is_equal(flag, "white"))
      return COLOR.WHITE;
    else if (is_equal(flag, "black"))
      return COLOR.BLACK;
  } else {
    if (is_equal(flag, "red"))
      return COLOR.RED_BG;
    else if (is_equal(flag, "green"))
      return COLOR.GREEN_BG;
    else if (is_equal(flag, "yellow"))
      return COLOR.YELLOW_BG;
    else if (is_equal(flag, "blue"))
      return COLOR.BLUE_BG;
    else if (is_equal(flag, "purple"))
      return COLOR.PURPLE_BG;
    else if (is_equal(flag, "cyan"))
      return COLOR.CYAN_BG;
    else if (is_equal(flag, "white"))
      return COLOR.WHITE_BG;
    else if (is_equal(flag, "black"))
      return COLOR.BLACK_BG;
    else if (is_equal(flag, "clear"))
      return COLOR.CLEAR;
  }

  show_status(1,
              "Invalid color. Type 'help setcolor' to see available colors.");

  return (char *)0;
}

// Parse and execute command
void parse_command(char *input) {
  // Initialize variables
  char command[MAX_CMD_SIZE];
  int i, j;

  // Extract command from input
  for (i = 0; input[i] != '\0' && input[i] != ' '; i++) {
    command[i] = input[i];
  }
  command[i] = '\0'; // Null-terminate the command

  // Skip spaces after command
  while (input[i] == ' ') {
    i++;
  }

  // Check for various commands
  if (is_equal(command, "help")) {
    // Extract the command to get help for
    char help_command[MAX_CMD_SIZE];
    j = 0;
    while (input[i] != '\0') {
      help_command[j++] = input[i++];
    }

    // Null-terminate the help command
    help_command[j] = '\0';

    // If help command is empty, treat as "all"
    if (len(help_command) == 0) {
      show_help("all");
    } else {
      show_help(help_command);
    }
  } else if (is_equal(command, "os")) {
    // Show OS information
    os_greet();
  } else if (is_equal(command, "clr") || is_equal(command, "cls") ||
             is_equal(command, "clear")) {

    // Parse the flags
    char *flags[MAX_CMD_SIZE];

    for (int i = 0; i < MAX_CMD_SIZE; i++) {
      flags[i] = (char *)0;
    }

    // Define the minimum and maximum flags required for the setcolor command
    int MIN_FLAGS = 0;
    int MAX_FLAGS = 1;

    // Parse the flags
    parse_flags(&input[i], flags, MAX_FLAGS, MIN_FLAGS);

    if (flags == (char **)0) {
      // Clear the terminal
      uart_puts("\033[2J \033[1;1H");
      return;
    }

    if (flags[0] == (char *)0) {
      // clear the terminal
      uart_puts("\033[2J \033[1;1H");
      return;
    }

    if (is_equal(flags[0], "f")) {
      // Clear everything from the terminal
      uart_puts("\033c");
      return;
    }

    // ERROR_COLOR message
    show_status(1, "Invalid flag. Type 'help clear' to see available flags.");
  } else if (is_equal(command, "hist")) {
    // Show command history
    uart_puts("\n");
  } else if (is_equal(command, "setcolor")) {
    // Extract the flags
    char *flags[MAX_CMD_SIZE];

    for (int i = 0; i < MAX_CMD_SIZE; i++) {
      flags[i] = (char *)0;
    }

    // Define the minimum and maximum flags required for the setcolor command
    int MIN_FLAGS = 1;
    int MAX_FLAGS = 3;

    // Parse the flags
    int flag_count = parse_flags(&input[i], flags, MAX_FLAGS, MIN_FLAGS);
    if (flag_count == 0) {
      return;
    }

    if (flags == (char **)0) {
      return;
    }

    char *color_option = (char *)0;

    for (int i = 0; i < flag_count; i++) {
      if (flags[i] == (char *)0) {
        break;
      }

      char target[MAX_CMD_SIZE];
      char option[MAX_CMD_SIZE];

      parse_target(flags[i], target, option);

      if (is_equal(target, "b")) {
        color_option = to_color(option, 1);

        if (color_option == (char *)0) {
          return;
        }

        THEME.BACKGROUND_COLOR = color_option;

      } else if (is_equal(target, "t")) {
        // t flag requires type and color
        color_option = to_color(option, 0);
        if (color_option == (char *)0) {
          return;
        }

        THEME.PRIMARY_COLOR = color_option;
        THEME.SECONDARY_COLOR = color_option;

      } else if (is_equal(target, "os")) {
        if (is_equal(option, "bright")) {
          THEME.PRIMARY_COLOR = COLOR.YELLOW;
          THEME.SECONDARY_COLOR = COLOR.WHITE;
          THEME.BACKGROUND_COLOR = COLOR.CLEAR;
          THEME.SUCCESS_COLOR = COLOR.GREEN;
          THEME.ERROR_COLOR = COLOR.RED;
        } else if (is_equal(option, "dark")) {
          THEME.PRIMARY_COLOR = COLOR.CYAN;
          THEME.SECONDARY_COLOR = COLOR.WHITE;
          THEME.BACKGROUND_COLOR = COLOR.BLACK_BG;
          THEME.SUCCESS_COLOR = COLOR.GREEN;
          THEME.ERROR_COLOR = COLOR.RED;
        } else if (is_equal(option, "light")) {
          THEME.PRIMARY_COLOR = COLOR.BLUE;
          THEME.SECONDARY_COLOR = COLOR.BLACK;
          THEME.BACKGROUND_COLOR = COLOR.WHITE_BG;
          THEME.SUCCESS_COLOR = COLOR.GREEN;
          THEME.ERROR_COLOR = COLOR.RED;
        } else {
          show_status(
              1,
              "Invalid theme. Type 'help setcolor' to see available themes.");
          return;
        }
      } else if (is_equal(target, "pri")) {
        color_option = to_color(option, 0);

        if (color_option == (char *)0) {
          return;
        }

        THEME.PRIMARY_COLOR = color_option;
      } else if (is_equal(target, "sec")) {
        color_option = to_color(option, 0);

        if (color_option == (char *)0) {
          return;
        }

        THEME.SECONDARY_COLOR = color_option;
      } else if (is_equal(target, "err")) {
        color_option = to_color(option, 0);

        if (color_option == (char *)0) {
          return;
        }

        THEME.ERROR_COLOR = color_option;
      } else if (is_equal(target, "suc")) {
        color_option = to_color(option, 0);

        if (color_option == (char *)0) {
          return;
        }

        THEME.SUCCESS_COLOR = color_option;
      } else {
        show_status(
            1,
            "Invalid command. Type 'help setcolor' to see available targets.");
        return;
      }
    }

    // SUCCESS_COLOR message
    show_status(0, "Color set successfully.");
  } else if (is_equal(command, "ref")) {
    // Extract the flags
    char *flags[MAX_CMD_SIZE];

    for (int i = 0; i < MAX_CMD_SIZE; i++) {
      flags[i] = (char *)0;
    }

    // Define the minimum and maximum flags required for the setcolor
    // command
    const int MIN_FLAGS = 2;
    const int MAX_FLAGS = 10;

    // Parse the flags
    parse_flags(&input[i], flags, MAX_FLAGS, MIN_FLAGS);
    if (flags == (char **)0) {
      return;
    }

    if (is_equal(flags[0], "uart")) {
      for (int i = 1; i < MAX_FLAGS; i++) {
        if (flags[i] == (char *)0) {
          break;
        }

        char target[MAX_CMD_SIZE];
        char option[MAX_CMD_SIZE];

        parse_target(flags[i], target, option);

        if (option == (char *)0) {
          show_status(
              1, "Invalid value. Type 'help ref' to see available targets.");
          return;
        }

        if (is_equal(target, "baud")) {
          BaudRateConfig baud_rate = get_baud_rate(string_to_int(option));

          uart_puts("\n");

          str_format("Baud Rate Configuration\n", THEME.PRIMARY_COLOR,
                     THEME.BACKGROUND_COLOR);

          str_format("IBRD: ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
          char ibrd[MAX_CMD_SIZE];
          int_to_string(baud_rate.ibrd, ibrd);
          str_format(ibrd, THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);

          uart_puts("\n");

          str_format("FBRD: ", THEME.PRIMARY_COLOR, THEME.BACKGROUND_COLOR);
          char fbrd[MAX_CMD_SIZE];
          int_to_string(baud_rate.fbrd, fbrd);
          str_format(fbrd, THEME.SECONDARY_COLOR, THEME.BACKGROUND_COLOR);

          uart_puts("\n");

          BAUD_RATE_CONFIG.ibrd = baud_rate.ibrd;
          BAUD_RATE_CONFIG.fbrd = baud_rate.fbrd;

          // SUCCESS_COLOR message
          show_status(0, "Baud rate set successfully.");
        } else if (is_equal(target, "dbits")) {
          DATA_BITS_CONFIG = string_to_int(option);

          if (DATA_BITS_CONFIG < 5 || DATA_BITS_CONFIG > 8) {
            show_status(
                1, "Invalid data bits. Data bits must be between 5 and 8.");
            return;
          }

          // SUCCESS_COLOR message
          show_status(0, "Data bits set successfully.");
        } else if (is_equal(target, "sbits")) {
          int val = string_to_int(option);
          if (val != 1 && val != 2) {
            show_status(1,
                        "Invalid stop bits. Stop bits must be either 1 or 2.");
            return;
          }

          STOP_BIT_CONFIG = val;

          // SUCCESS_COLOR message
          show_status(0, "Stop bits set successfully.");
        } else if (is_equal(target, "par")) {
          if (option == (char *)0) {
            show_status(
                1, "Invalid parity. Parity must be either none, even or odd.");
            return;
          }

          int val = string_to_int(option);
          if (val < 0 || val > 2) {
            show_status(1, "Invalid parity. Parity must be either none (0), "
                           "odd (1) or even (2).");
            return;
          }

          PARITY_CONFIG = val;
          show_status(0, "Parity set successfully.");
        } else if (is_equal(target, "handshake")) {
          if (option == (char *)0) {
            show_status(1, "Invalid handshake. Handshake must be either "
                           "CTS/RTS (1) or none (0) ");
            return;
          }

          int val = string_to_int(option);

          if (val < 0 || val > 1) {
            show_status(1, "Invalid handshake. Handshake must be either "
                           "CTS/RTS (1) or none (0) ");
            return;
          }

          // SUCCESS_COLOR message
          HANDSHAKE_CONFIG = string_to_int(option);
          show_status(0, "Handshake set successfully.");
        } else {
          show_status(
              1, "Invalid command. Type 'help ref' to see available targets.");
          return;
        }
      }
      IS_REINIT_UART = 1;
    } else {
      str_format("\n\nInvalid command. Type 'help ref' to see available "
                 "targets.\n",
                 THEME.ERROR_COLOR, THEME.BACKGROUND_COLOR);
      return;
    }
  } else if (is_equal(command, "showinfo")) {
    uart_puts("\n\n");

    // Extract the flags
    char *flags[MAX_CMD_SIZE];

    for (int i = 0; i < MAX_CMD_SIZE; i++) {
      flags[i] = (char *)0;
    }

    // Define the minimum and maximum flags required for the setcolor
    // command
    const int MIN_FLAGS = 0;
    const int MAX_FLAGS = 1;

    // Parse the flags
    parse_flags(&input[i], flags, MAX_FLAGS, MIN_FLAGS);

    // Tabulate the device information
    char *keys[] = {"Board", "Value"};
    char *values[MAX_ROWS][MAX_ROWS];

    // Initialize the values array
    initialize_values(values, 2);

    // Get MAC Address
    mBuf[0] = 12 * 4;       // Buffer size in bytes
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = 0x00010003;   // TAG Identifier: Get Mac Address
    mBuf[3] = 8;
    mBuf[4] = 0;
    mBuf[5] = 0;
    mBuf[6] = 0; // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[7] = MBOX_TAG_LAST;
    char mac_address[18];

    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
      // Convert the MAC Address to a string
      mac_address_format(mBuf[5], mBuf[6], mac_address);

      values[0][0] = "MAC Address";
      values[0][1] = mac_address;

    } else {
      show_status(1, "Failed to query MAC Address.");
    }

    // Get revision number
    mBuf[0] = 7 * 4;        // Buffer size in bytes
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = 0x00010002;   // TAG Identifier: Get Board Revision
    mBuf[3] = 4;
    mBuf[4] = 0;
    mBuf[5] = 0; // clear output buffer (response data are mBuf[5])
    mBuf[6] = MBOX_TAG_LAST;

    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
      values[1][0] = "Board Revision Number";
      values[1][1] = hex_to_string(mBuf[5]);
    } else {
      show_status(1, "Failed to query Board Revision.");
    }

    tabulate(keys, 2, values, 2);

    if (is_equal(flags[0], "v")) {

      char *keys[] = {"Uart", "Value"};
      char *values[MAX_ROWS][MAX_ROWS];

      // Initialize the values array
      initialize_values(values, 6);

      // Get uart baud rate
      values[0][0] = "UART Baud Rate (IBRD)";
      char ibrd[10];
      int_to_string(BAUD_RATE_CONFIG.ibrd, ibrd);
      values[0][1] = ibrd;

      values[1][0] = "UART Baud Rate (FBRD)";
      char fbrd[10];
      int_to_string(BAUD_RATE_CONFIG.fbrd, fbrd);
      values[1][1] = fbrd;

      values[2][0] = "Data Bits";
      char dbits[2];
      int_to_string(DATA_BITS_CONFIG, dbits);
      values[2][1] = dbits;

      values[3][0] = "Stop Bits";
      char sbits[2];
      int_to_string(STOP_BIT_CONFIG, sbits);
      values[3][1] = sbits;

      values[4][0] = "Parity";
      char parity[2];
      int_to_string(PARITY_CONFIG, parity);
      values[4][1] = parity;

      values[5][0] = "Handshake";
      char handshake[2];
      int_to_string(HANDSHAKE_CONFIG, handshake);
      values[5][1] = handshake;

      uart_puts("\n");
      tabulate(keys, 2, values, 6);
      return;
    }
  } else {
    show_status(1, "Command not found. Type 'help' to see available commands.");
  }
}