#ifndef OS_COMMAND
#define OS_COMMAND

#include "../global/global.h"
#include "../helper/styler/styler.h"
#include "../helper/utils/utils.h"
#include "../mbox/mbox.h"
#include "../uart/uart.h"

// Struct to store command stack
/*
 * The implementation of the CommandStack struct follows the same pattern as the
 * Stack struct. It has a top_index variable to keep track of the top element of
 * the stack and an array of strings to store the commands. The MAX_CMD_HISTORY
 * macro defines the maximum number of commands that can be stored in the stack,
 * and the MAX_CMD_SIZE macro defines the maximum size of each command.
 */
typedef struct CommandStack {

  char command[MAX_CMD_HISTORY][MAX_CMD_SIZE];
  int top_index;
} CommandStack;

// Function prototypes
void os_greet();                   // Welcome message
void show_help(char *command);     // Show help menu
void parse_command(char *command); // Parse the command

// Command stack methods
void push_command(struct CommandStack *stack, char *command); // Push command
void pop_command(struct CommandStack *stack);                 // Pop command
void get_command(struct CommandStack *stack);                 // Get command
void get_all_commands(struct CommandStack *stack); // Get all commands

// Command methods
char *autocomplete_command(char *buffer); // Autocomplete command

#endif