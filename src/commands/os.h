#ifndef OS_COMMAND
#define OS_COMMAND

#include "../global/global.h"
#include "../uart/uart.h"

#define MAX_LEN_HIST 10

// Struct to store command stack
typedef struct CommandStack {
  char command[MAX_LEN_HIST][MAX_CMD_SIZE];
  int top_index;
} CommandStack;

// Function prototypes
void os_greet();                   // Welcome message
void show_help(char *command);     // Show help menu
void parse_command(char *command); // Parse the command

// Command stack methods
void push_command(struct CommandStack *stack, char *command);
void pop_command(struct CommandStack *stack);
void get_command(struct CommandStack *stack);
void get_all_commands(struct CommandStack *stack);

#endif