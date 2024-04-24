#include "os.h"
#include "../global/global.h"
#include "../helper/styler/styler.h"
#include "../helper/utils/utils.h"

void os_greet() {
  uart_puts("\n");
  uart_puts("Triggering OS...\n");
  // Print OS logo
  str_format(OS_INF.ascii_art_logo, OS_CONFIG.PRIMARY_COLOR);
  uart_puts("\n");

  // Print OS Information box
  print_in_box("OS Information");
  uart_puts("\n");

  // Format and print "ID" title
  str_format("ID           : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(OS_INF.id, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Format and print "OS Name" title
  str_format("OS Name      : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(OS_INF.name, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Format and print "Version" title
  str_format("Version      : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(OS_INF.version, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Format and print "Home URL" title
  str_format("Home URL     : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(OS_INF.home_url, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Format and print "Support URL" title
  str_format("Support URL  : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(OS_INF.support_url, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Author Information
  print_in_box("Author Information");
  uart_puts("\n");

  // Print author name
  str_format("Author       : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(OS_INF.author.name, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Print author username
  str_format("Username     : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(OS_INF.author.username, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Print author SID
  str_format("SID          : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(OS_INF.author.sid, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Print author email
  str_format("Email        : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(OS_INF.author.email, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Copyright
  print_in_box("Acknowledgement");

  // Print school name (RMIT SSET)
  str_format("School       : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(ACK.school, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Print course name (Embedded Systems 3)
  str_format("Course       : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(ACK.course, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Print lecturer name (Mr. Linh T.D.)
  str_format("Lecturer     : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(ACK.lecturer, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Print submitted by
  str_format("Submitted by : ", OS_CONFIG.PRIMARY_COLOR);
  str_format(ACK.submitted_by, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n\n");

  // Print declaration
  str_format(ACK.declaration, OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");

  // Print OS logo
  str_format(OS_INF.ascii_art_name, OS_CONFIG.PRIMARY_COLOR);
  uart_puts("\n");

  str_format("@2024. All rights reserved.", OS_CONFIG.SECONDARY_COLOR);
  uart_puts("\n");
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
  char *commands[MAX_ROWS] = {0};
  char *commands_desc[MAX_ROWS][MAX_ROWS];

  // Ref: Help command on Linux
  uart_puts("\n\nBrightOS, Version 1.0\n");
  uart_puts("These shell commands are defined internally. Type 'help' to see "
            "this list.\n");
  uart_puts("Type 'help name' to find out more about the function 'name'.\n");
  uart_puts("A star (*) next to a name means that the command is disabled.\n");

  initialize_values(values, 11);        // Initialize the values array
  initialize_values(commands_desc, 11); // Initialize the commands_desc array

  commands[0] = "os";
  commands[1] = "help";
  commands[2] = "help [command]";
  commands[3] = "clr / cls / clear";
  commands[4] = "hist";
  commands[5] = "setcolor";
  commands[6] = "ref";
  commands[7] = "showinfo";
  commands[8] = "auth";
  commands[9] = (char *)0;

  commands_desc[0][0] = "Show OS information";
  commands_desc[1][0] = "Show all commands";
  commands_desc[2][0] = "Show help for a command";
  commands_desc[3][0] = "Clear the terminal";
  commands_desc[4][0] = "Show command history";
  commands_desc[5][0] = "Change color of OS";
  commands_desc[5][1] = "-[element]: b: background, t: text";
  commands_desc[5][2] = "-[type]: p: primary, s: secondary, a: all";
  commands_desc[5][3] =
      "-[color]: red, green, yellow, blue, purple, cyan, white, "
      "black";
  commands_desc[5][4] = "\nE.g.: setcolor -b -p -red";
  commands_desc[6][0] = "Show reference for a target";
  commands_desc[6][1] = "-[target]: os, option: -c -theme -<dark/light/bright>";
  commands_desc[6][2] =
      "-[target]: uart, options: -c -baud <bits_per_second>, -c "
      "-dbits <5/6/7/8>, -c -sbits <1/2>, -c -par "
      "<none/even/odd>, -c -handshake <CTS/RTS>";
  commands_desc[6][3] = "\nE.g.: ref -os -theme -dark";
  commands_desc[6][4] =
      "\nE.g.: ref -uart -baud 9600 -dbits 8 -sbits 1 -par none "
      "-handshake CTS";
  commands_desc[7][0] = "Show current device information";
  commands_desc[7][1] = "-concise: show concise information";
  commands_desc[7][2] = "-full: show full information";
  commands_desc[7][3] = "\nE.g.: showinfo -concise";
  commands_desc[8][0] = "Authenticate user";
  commands_desc[8][1] = "-[arg]: lg/reg";
  commands_desc[8][2] = "-u: username";
  commands_desc[8][3] = "-p: password";
  commands_desc[8][4] = "-out: logout";
  commands_desc[8][5] = "\nE.g.: auth -lg -u <username> -p <password>";
  commands_desc[10][0] = (char *)0;

  // Display help menu
  print_in_box("Help Menu");
  uart_puts("\n");

  // Display commands in tabular format
  int num_rows = 0;
  if (is_equal(command, "all") == 0) {
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
      if (is_equal(command, commands[i]) == 0) {
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
      uart_puts("\nCommand not found.\n");
      return;
    }
  }

  tabulate(keys, 2, values, num_rows);
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
    help_command[j] = '\0'; // Null-terminate the help command

    // If help command is empty, treat as "all"
    if (len(help_command) == 0) {
      show_help("all");
    } else {
      show_help(help_command);
    }
  } else if (is_equal(command, "os")) {
    os_greet();
  } else if (is_equal(command, "clr") || is_equal(command, "cls") ||
             is_equal(command, "clear")) {
    uart_puts("\033c"); // Full terminal reset
  } else if (is_equal(command, "hist")) {
    uart_puts("\n");
  } else if (is_equal(command, "setcolor")) {
    char element[MAX_CMD];
    char type[MAX_CMD];
    char color[MAX_CMD];
    int flag_index = 0;
    int j = 0;

    while (input[i] != '\0') {
      // Flag start
      if (input[i] == '-') {
        flag_index++;
        i++;
        j = 0; // Reset j after each flag
        continue;
      }

      // Extract the flags
      if (input[i] != ' ') {
        if (flag_index == 1 && j < MAX_CMD - 1) {
          element[j++] = input[i];
        } else if (flag_index == 2 && j < MAX_CMD - 1) {
          type[j++] = input[i];
        } else if (flag_index == 3 && j < MAX_CMD - 1) {
          color[j++] = input[i];
        }
      }

      // Null terminate strings when encountering space
      if (input[i] == ' ') {
        if (flag_index == 1) {
          element[j] = '\0';
        } else if (flag_index == 2) {
          type[j] = '\0';
        } else if (flag_index == 3) {
          color[j] = '\0';
        }
        j = 0; // Reset j after each flag
      }
      i++;
    }

    char *color_option;

    if (is_equal(color, "red")) {
      color_option = COLOR.RED;
    } else if (is_equal(color, "green")) {
      color_option = COLOR.GREEN;
    } else if (is_equal(color, "yellow")) {
      color_option = COLOR.YELLOW;
    } else if (is_equal(color, "blue")) {
      color_option = COLOR.BLUE;
    } else if (is_equal(color, "purple")) {
      color_option = COLOR.PURPLE;
    } else if (is_equal(color, "cyan")) {
      color_option = COLOR.CYAN;
    } else if (is_equal(color, "white")) {
      color_option = COLOR.WHITE;
    } else if (is_equal(color, "black")) {
      color_option = COLOR.BLACK;
    } else {
      uart_puts(
          "\nInvalid color. Type 'help setcolor' to see available colors.");
      return;
    }

    if (is_equal(element, "t")) {
      if (is_equal(type, "p")) {
        OS_CONFIG.PRIMARY_COLOR = color_option;
      } else if (is_equal(type, "s")) {
        OS_CONFIG.SECONDARY_COLOR = color_option;
      } else if (is_equal(type, "a")) {
        OS_CONFIG.PRIMARY_COLOR = color_option;
        OS_CONFIG.SECONDARY_COLOR = color_option;
      } else {
        uart_puts(
            "\nInvalid type. Type 'help setcolor' to see available types.");
        return;
      }

    } else if (is_equal(element, "b")) {
      OS_CONFIG.BACKGROUND_COLOR = color_option;
    } else {
      uart_puts("\nInvalid element. Type 'help setcolor' to see available "
                "elements.");
      return;
    }

    // Print success message
    uart_puts("\nColor changed successfully.");
  } else {
    uart_puts("\nInvalid command. Type 'help' to see available commands.");
  }
}
