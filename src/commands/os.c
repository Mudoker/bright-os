#include "os.h"
#include "../global/global.h"
#include "../helper/styler/styler.h"
#include "../helper/utils/utils.h"
#include "../mbox/mbox.h"

char *commands[] = {"os",       "help", "help <name>", "clr/cls/clear", "hist",
                    "setcolor", "ref",  "showinfo",    (char *)0};

void os_greet() {
  uart_puts("\n");

  // Print OS logo
  str_format(OS_INF.ascii_art_logo, OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print OS Information box
  print_in_box("OS Information");
  uart_puts("\n");

  // Format and print "ID" title
  str_format("ID           : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(OS_INF.id, OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Format and print "OS Name" title
  str_format("OS Name      : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(OS_INF.name, OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Format and print "Version" title
  str_format("Version      : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(OS_INF.version, OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Format and print "Home URL" title
  str_format("Home URL     : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(OS_INF.home_url, OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Format and print "Support URL" title
  str_format("Support URL  : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(OS_INF.support_url, OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Author Information
  print_in_box("Author Information");
  uart_puts("\n");

  // Print author name
  str_format("Author       : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(OS_INF.author.name, OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print author username
  str_format("Username     : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(OS_INF.author.username, OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print author SID
  str_format("SID          : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(OS_INF.author.sid, OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print author email
  str_format("Email        : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(OS_INF.author.email, OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Copyright
  print_in_box("Acknowledgement");
  uart_puts("\n");

  // Print school name (RMIT SSET)
  str_format("School       : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(ACK.school, OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print course name (Embedded Systems 3)
  str_format("Course       : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(ACK.course, OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print lecturer name (Mr. Linh T.D.)
  str_format("Lecturer     : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(ACK.lecturer, OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print submitted by
  str_format("Submitted by : ", OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format(ACK.submitted_by, OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n\n");

  // Print declaration
  str_format(ACK.declaration, OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  // Print OS logo
  str_format(OS_INF.ascii_art_name, OS_CONFIG.PRIMARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n");

  str_format("@2024. All rights reserved.", OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  uart_puts("\n\n");
}

// As per limitations of bare-metal programming, the stack is implemented as
// using a fixed-size array
// Command stack methods
void push_command(struct CommandStack *stack, char *command) {
  // Check if the stack is full
  if (stack->top_index == MAX_LEN_HIST - 1) {
    // Shift the stack to the left
    for (int i = 0; i < MAX_LEN_HIST - 1; i++) {
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
  str_format("\n\nBrightOS, Version 1.0\n", OS_CONFIG.SECONDARY_COLOR,
             OS_CONFIG.BACKGROUND_COLOR);
  str_format("These shell commands are defined internally. Type 'help' to see "
             "this list.\n",
             OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  str_format("Type 'help name' to find out more about the function 'name'.\n ",
             OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);
  str_format("A star (*) next to a name means that the command is disabled.\n ",
             OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);

  initialize_values(values, 9);        // Initialize the values array
  initialize_values(commands_desc, 9); // Initialize the commands_desc array

  commands_desc[0][0] = "Show OS information";
  commands_desc[1][0] = "Show all commands";
  commands_desc[2][0] = "Show help for a command";
  commands_desc[3][0] = "Clear the terminal";
  commands_desc[4][0] = "Show command history";
  commands_desc[5][0] = "Change color of OS";
  commands_desc[5][1] =
      "-[target]: b: background, t: text, os: os theme, "
      "pri: primary, sec: secondary, err: error, suc: success";
  commands_desc[5][2] =
      "-[color]: red, green, yellow, blue, purple, cyan, white, "
      "black, bright (os only), dark (os only), light (os only)";
  commands_desc[5][3] =
      "\nE.g.: setcolor -t red -b yellow -pri green -sec cyan";
  commands_desc[6][0] = "Show reference for a target";
  commands_desc[6][1] =
      "-[target]: uart, options: -baud <bits_per_second>, -dbits <5/6/7/8>, "
      "-sbits <1/2>, -par "
      "<none/even/odd>, -c -handshake <CTS/RTS>";
  commands_desc[6][2] = "\nE.g.: ref -uart -baud 115200 -dbits 8 -sbits 1 -par "
                        "none -c -handshake CTS";
  commands_desc[6][3] =
      "\nE.g.: ref -uart -baud 9600 -dbits 8 -sbits 1 -par none "
      "-handshake CTS";
  commands_desc[7][0] = "Show current device information";
  commands_desc[7][1] = "-concise: show concise information";
  commands_desc[7][2] = "-full (default): show full information";
  commands_desc[7][3] = "\nE.g.: showinfo -concise";
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
      str_format("Command not found. Type 'help' to see available commands.\n",
                 OS_CONFIG.ERROR, OS_CONFIG.BACKGROUND_COLOR);
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

  return (char *)0;
}

// Parse flags from the input
int parse_flags(char *input, char *flags[], int max_flags, int min_flags) {
  int i = 0;
  int j = 0;
  int k = 0;
  int flag_count = 0;
  char flag_buffer[MAX_CMD_SIZE][MAX_CMD];

  for (int i = 0; i < MAX_CMD_SIZE; i++) {
    for (int j = 0; j < MAX_CMD; j++) {
      flag_buffer[i][j] = '\0';
    }
  }

  while (input[i] != '\0' && k < MAX_CMD) {
    if (input[i] == '-') {
      i++;
      j = 0; // Reset j for a new flag
      flag_count++;

      while (input[i] != '\0' && input[i + 1] != '-' && j < MAX_CMD - 1) {
        flag_buffer[k][j++] = input[i++];
      }

      flag_buffer[k][j] = '\0'; // Null-terminate the flag string
      // flags[k] = flag_buffer[k]; // Assign the flag to the flags array
      flags[0] = flag_buffer[0]; // Assign the flag to the flags array
      flags[1] = flag_buffer[1]; // Assign the flag to the flags array
      k++;                       // Increment index for the flags array
    }
    i++;
  }

  // Check if the number of flags exceeds the maximum allowed flags
  if (flag_count > max_flags) {
    str_format(
        "\nToo many flags. Type 'help <command>' to see available flags.",
        OS_CONFIG.ERROR, OS_CONFIG.BACKGROUND_COLOR);
    return 0;
  }

  // Check if the number of flags is less than the minimum required flags
  if (flag_count < min_flags) {
    str_format("\nToo few flags. Type 'help <command>' to see available flags.",
               OS_CONFIG.ERROR, OS_CONFIG.BACKGROUND_COLOR);
    return 0;
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
  char *color_option = (char *)0;

  if (type == 0) {
    if (is_equal(flag, "red")) {
      color_option = COLOR.RED;
    } else if (is_equal(flag, "green")) {
      color_option = COLOR.GREEN;
    } else if (is_equal(flag, "yellow")) {
      color_option = COLOR.YELLOW;
    } else if (is_equal(flag, "blue")) {
      color_option = COLOR.BLUE;
    } else if (is_equal(flag, "purple")) {
      color_option = COLOR.PURPLE;
    } else if (is_equal(flag, "cyan")) {
      color_option = COLOR.CYAN;
    } else if (is_equal(flag, "white")) {
      color_option = COLOR.WHITE;
    } else if (is_equal(flag, "black")) {
      color_option = COLOR.BLACK;
    } else {
      str_format(
          "\nInvalid color. Type 'help setcolor' to see available colors.",
          OS_CONFIG.ERROR, OS_CONFIG.BACKGROUND_COLOR);
      return (char *)0;
    }
  } else {
    if (is_equal(flag, "red")) {
      color_option = COLOR.RED_BG;
    } else if (is_equal(flag, "green")) {
      color_option = COLOR.GREEN_BG;
    } else if (is_equal(flag, "yellow")) {
      color_option = COLOR.YELLOW_BG;
    } else if (is_equal(flag, "blue")) {
      color_option = COLOR.BLUE_BG;
    } else if (is_equal(flag, "purple")) {
      color_option = COLOR.PURPLE_BG;
    } else if (is_equal(flag, "cyan")) {
      color_option = COLOR.CYAN_BG;
    } else if (is_equal(flag, "white")) {
      color_option = COLOR.WHITE_BG;
    } else if (is_equal(flag, "black")) {
      color_option = COLOR.BLACK_BG;
    } else if (is_equal(flag, "reset")) {
      color_option = COLOR.RESET;
    } else {
      str_format(
          "\nInvalid color. Type 'help setcolor' to see available colors.",
          OS_CONFIG.ERROR, OS_CONFIG.BACKGROUND_COLOR);
      return (char *)0;
    }
  }

  return color_option;
}

// Parse and execute command
void parse_command(char *input) {
  // Initialize variables
  char command[MAX_CMD];
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
    char help_command[MAX_CMD];
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
    // Clear the terminal
    uart_puts("\033[2J \033[1;1H");
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

        OS_CONFIG.BACKGROUND_COLOR = color_option;

      } else if (is_equal(target, "t")) {
        // t flag requires type and color
        color_option = to_color(option, 0);
        if (color_option == (char *)0) {
          return;
        }

        OS_CONFIG.PRIMARY_COLOR = color_option;
        OS_CONFIG.SECONDARY_COLOR = color_option;

      } else if (is_equal(target, "os")) {
        if (is_equal(option, "bright")) {
          OS_CONFIG.PRIMARY_COLOR = COLOR.YELLOW;
          OS_CONFIG.SECONDARY_COLOR = COLOR.WHITE;
          OS_CONFIG.BACKGROUND_COLOR = COLOR.RESET;
          OS_CONFIG.SUCCESS = COLOR.GREEN;
          OS_CONFIG.ERROR = COLOR.RED;
        } else if (is_equal(option, "dark")) {
          OS_CONFIG.PRIMARY_COLOR = COLOR.CYAN;
          OS_CONFIG.SECONDARY_COLOR = COLOR.WHITE;
          OS_CONFIG.BACKGROUND_COLOR = COLOR.BLACK_BG;
          OS_CONFIG.SUCCESS = COLOR.GREEN;
          OS_CONFIG.ERROR = COLOR.RED;
        } else if (is_equal(option, "light")) {
          OS_CONFIG.PRIMARY_COLOR = COLOR.BLUE;
          OS_CONFIG.SECONDARY_COLOR = COLOR.BLACK;
          OS_CONFIG.BACKGROUND_COLOR = COLOR.WHITE_BG;
          OS_CONFIG.SUCCESS = COLOR.GREEN;
          OS_CONFIG.ERROR = COLOR.RED;
        } else {
          str_format(
              "\nInvalid theme. Type 'help setcolor' to see available themes.",
              OS_CONFIG.ERROR, OS_CONFIG.BACKGROUND_COLOR);
          return;
        }
      } else if (is_equal(target, "pri")) {
        color_option = to_color(option, 0);

        if (color_option == (char *)0) {
          return;
        }

        OS_CONFIG.PRIMARY_COLOR = color_option;
      } else if (is_equal(target, "sec")) {
        color_option = to_color(option, 0);

        if (color_option == (char *)0) {
          return;
        }

        OS_CONFIG.SECONDARY_COLOR = color_option;
      } else if (is_equal(target, "err")) {
        color_option = to_color(option, 0);

        if (color_option == (char *)0) {
          return;
        }

        OS_CONFIG.ERROR = color_option;
      } else if (is_equal(target, "suc")) {
        color_option = to_color(option, 0);

        if (color_option == (char *)0) {
          return;
        }

        OS_CONFIG.SUCCESS = color_option;
      } else {
        str_format(
            "\nInvalid command. Type 'help setcolor' to see available targets.",
            OS_CONFIG.ERROR, OS_CONFIG.BACKGROUND_COLOR);
        return;
      }
    }

    // Success message
    str_format("\nColor set successfully.\n", OS_CONFIG.SUCCESS,
               OS_CONFIG.BACKGROUND_COLOR);
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

        if (is_equal(target, "baud")) {
          if (option == (char *)0) {
            str_format(
                "Invalid command. Type 'help ref' to see available targets.",
                OS_CONFIG.ERROR, OS_CONFIG.BACKGROUND_COLOR);
            return;
          }

          BaudRateConfig baud_rate = get_baud_rate(string_to_int(option));

          uart_puts("\n");

          str_format("Baud Rate Configuration\n", OS_CONFIG.PRIMARY_COLOR,
                     OS_CONFIG.BACKGROUND_COLOR);

          str_format("IBRD: ", OS_CONFIG.PRIMARY_COLOR,
                     OS_CONFIG.BACKGROUND_COLOR);
          char ibrd[MAX_CMD_SIZE];
          int_to_string(baud_rate.ibrd, ibrd);
          str_format(ibrd, OS_CONFIG.SECONDARY_COLOR,
                     OS_CONFIG.BACKGROUND_COLOR);

          uart_puts("\n");

          str_format("FBRD: ", OS_CONFIG.PRIMARY_COLOR,
                     OS_CONFIG.BACKGROUND_COLOR);
          char fbrd[MAX_CMD_SIZE];
          int_to_string(baud_rate.fbrd, fbrd);
          str_format(fbrd, OS_CONFIG.SECONDARY_COLOR,
                     OS_CONFIG.BACKGROUND_COLOR);
          uart_puts("\n");

          BAUD_RATE_CONFIG.ibrd = baud_rate.ibrd;
          BAUD_RATE_CONFIG.fbrd = baud_rate.fbrd;

          // Success message
          str_format("\nBaud rate set successfully.\n", OS_CONFIG.SUCCESS,
                     OS_CONFIG.BACKGROUND_COLOR);
        } else {
          uart_puts("\n");

          str_format("Invalid command. Type 'help ref' to see available "
                     "targets.",
                     OS_CONFIG.ERROR, OS_CONFIG.BACKGROUND_COLOR);
          return;
        }
      }
    } else {
      str_format("Invalid command. Type 'help ref' to see available "
                 "targets.",
                 OS_CONFIG.ERROR, OS_CONFIG.BACKGROUND_COLOR);
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
    initialize_values(values, 4);

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
      unsigned int num1 = 0x12005452;
      unsigned int num2 = 0x00005734;

      // Convert the MAC Address to a string
      convertToMacAddress(num1, num2, mac_address);

      values[0][0] = "MAC Address";
      values[0][1] = mac_address;
    } else {
      str_format("Failed to query MAC Address.\n", OS_CONFIG.ERROR,
                 OS_CONFIG.BACKGROUND_COLOR);
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
      str_format("Failed to query Board Revision.\n", OS_CONFIG.ERROR,
                 OS_CONFIG.BACKGROUND_COLOR);
    }

    tabulate(keys, 2, values, 2);

    if (is_equal(flags[0], "v")) {

      char *keys[] = {"Uart", "Value"};
      char *values[MAX_ROWS][MAX_ROWS];

      // Initialize the values array
      initialize_values(values, 2);

      // Get uart baud rate
      values[0][0] = "UART Baud Rate (IBRD)";
      char ibrd[10];
      int_to_string(BAUD_RATE_CONFIG.ibrd, ibrd);
      values[0][1] = ibrd;

      values[1][0] = "UART Baud Rate (FBRD)";
      char fbrd[10];
      int_to_string(BAUD_RATE_CONFIG.fbrd, fbrd);
      values[1][1] = fbrd;

      uart_puts("\n");
      tabulate(keys, 2, values, 2);
      return;
    }
  } else {
    str_format("\nCommand not found. Type 'help' to see available commands.\n",
               OS_CONFIG.ERROR, OS_CONFIG.BACKGROUND_COLOR);
  }
}