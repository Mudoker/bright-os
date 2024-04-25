#ifndef GLOBAL_H
#define GLOBAL_H

// Author structure
typedef struct {
  char *name;     // Author name
  char *username; // Author username
  char *email;    // Author email
  char *sid;      // Author student id
} Author;

// OS trademark structure
typedef struct {
  char *ascii_art_name; // OS ascii art name
  char *ascii_art_logo; // OS logo
  char *name;           // OS name
  char *id;             // OS id
  char *home_url;       // OS home url (tba)
  char *support_url;    // OS support url (tba)
  char *version;        // OS version
  char *created_at;     // OS created date
  char *updated_at;     // OS updated date
  char *init;    // OS init (Initial text displayed in the console of the OS)
  Author author; // OS author
} OsTrademark;

// Command structure
typedef struct {
  char *name;         // Name of the command
  char *desc;         // Description of the command
  void (*func)(void); // Function pointer to the command
} Command;

// Acknowledgement structure
typedef struct {
  char *school;       // School name
  char *course;       // Course name
  char *lecturer;     // Lecturer name
  char *submitted_by; // Submitted by
  char *declaration;  // Declaration
} Acknowledgement;

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
  char *RESET;     // Reset color
} Color;

// Styler structure
typedef struct {
  char *BOLD_ON;       // Bold on
  char *ITALIC_ON;     // Italic on
  char *UNDERLINE_ON;  // Underline on
  char *BOLD_OFF;      // Bold off
  char *ITALIC_OFF;    // Italic off
  char *UNDERLINE_OFF; // Underline off
  char *DEFAULT;       // Default style (Bold off)
} Styler;

typedef struct {
  char *PRIMARY_COLOR;    // Primary color (Default: Yellow)
  char *SECONDARY_COLOR;  // Secondary color (Default: White)
  char *BACKGROUND_COLOR; // Background color (Default: Black)
  char *SUCCESS;          // Success (Default: Green)
  char *ERROR;            // Error (Default: Red)
  char *THEME;            // Theme (Default: None)
} OsConfig;

typedef struct {
  unsigned int ibrd;
  unsigned int fbrd;
} BaudRateConfig;

// Configuration settings
#define MAX_CMD_SIZE 100 // Maximum command size
#define MAX_CMD 50       // Maximum number of commands
#define MAX_STR_LEN 1000 // Maximum number of string length

// Global variables
extern Color COLOR;
extern OsTrademark OS_INF;
extern Acknowledgement ACK;
extern Styler STYLER;
extern OsConfig OS_CONFIG;
extern BaudRateConfig BAUD_RATE_CONFIG;

#endif