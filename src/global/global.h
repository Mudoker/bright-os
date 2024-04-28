#ifndef GLOBAL_H
#define GLOBAL_H

// Contents: global variables and structures
#define MAX_CMD_SIZE 200    // Maximum command size
#define MAX_STR_LEN 1000    // Maximum number of string length
#define MAX_ARG_SIZE 100    // Maximum number of arguments size
#define MAX_CMD_HISTORY 100 // Maximum number of command history

// OS trademark structure
typedef struct {
  // OS information
  const char *ASCII_ART_LOGO;      // OS logo
  const char *ASCII_ART_LOGO_TEXT; // OS logo small
  const char *OS_NAME;             // OS name
  const char *OS_ID;               // OS id
  const char *OS_VERSION;          // OS version
  const char *CREATED_AT;          // OS created date
  const char *UPDATED_AT;          // OS updated date
  const char *PROMPT;              // Prompt symbol (Default: BrightOS>)

  // Author
  const char *AUTHOR_NAME;       // Author name
  const char *AUTHOR_USERNAME;   // Author username
  const char *AUTHOR_EMAIL;      // Author email
  const char *AUTHOR_SID;        // Author student id
  const char *AUTHOR_GITHUB_URL; // Author github

  // Acknowledgement
  const char *ACK_SCHOOL;       // School name
  const char *ACK_COURSE;       // Course name
  const char *ACK_LECTURER;     // Lecturer name
  const char *ACK_SUBMITTED_BY; // Submitted by
  const char *ACK_DECLARATION;  // Declaration
} Information;

// Theme color
typedef struct {
  char *RED;       // Red color
  char *GREEN;     // Green color
  char *YELLOW;    // Yellow color
  char *BLUE;      // Blue color
  char *PURPLE;    // Purple color
  char *CYAN;      // Cyan color
  char *WHITE;     // White color
  char *BLACK;     // Black color
  char *RED_BG;    // Red background color
  char *GREEN_BG;  // Green background color
  char *YELLOW_BG; // Yellow background color
  char *BLUE_BG;   // Blue background color
  char *PURPLE_BG; // Purple background color
  char *CYAN_BG;   // Cyan background color
  char *WHITE_BG;  // White background color
  char *BLACK_BG;  // Black background color
  char *CLEAR;     // Clear background color
} Color;

typedef struct {
  char *PRIMARY_COLOR;    // Primary color (Default: Yellow)
  char *SECONDARY_COLOR;  // Secondary color (Default: White)
  char *BACKGROUND_COLOR; // Background color (Default: Black)
  char *SUCCESS_COLOR;    // Success (Default: Green)
  char *ERROR_COLOR;      // Error (Default: Red)
} Theme;

typedef struct {
  unsigned int ibrd; // Integer baud rate divisor
  unsigned int fbrd; // Fractional baud rate divisor
} BaudRateConfig;

// Global variables and structures
extern Color COLOR;                     // Color options
extern Information OS_INFO;             // OS trademark information
extern Theme THEME;                     // Theme configuration
extern BaudRateConfig BAUD_RATE_CONFIG; // Baud rate configuration
extern int DATA_BITS_CONFIG;            // Data bits configuration
extern int STOP_BIT_CONFIG;             // Stop bit configuration
extern int PARITY_CONFIG;               // Parity configuration
extern int HANDSHAKE_CONFIG;            // Handshake configuration
extern int IS_REINIT_UART;              // UART reinitialization state

#endif