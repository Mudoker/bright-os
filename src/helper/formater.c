#include "../global/headers/format.h"

// Function to format string with color and print it
void format_and_print(char *str, const char *color, int bold, int italic)
{
    char *color_code = "";
    char *style_code = "";

    // Assign color code based on the provided color string
    if (strcmp(color, "red") == 0)
    {
        color_code = "\x1b[31m"; // Red
    }
    else if (strcmp(color, "green") == 0)
    {
        color_code = "\x1b[32m"; // Green
    }
    else if (strcmp(color, "yellow") == 0)
    {
        color_code = "\x1b[33m"; // Yellow
    }
    else if (strcmp(color, "blue") == 0)
    {
        color_code = "\x1b[34m"; // Blue
    }
    else if (strcmp(color, "magenta") == 0)
    {
        color_code = "\x1b[35m"; // Magenta
    }
    else if (strcmp(color, "cyan") == 0)
    {
        color_code = "\x1b[36m"; // Cyan
    }
    else
    {
        color_code = ANSI_COLOR_RESET; // Default color
    }

    // Assign style code based on bold and italic flags
    if (bold && italic)
    {
        style_code = "\x1b[1;3m"; // Bold and Italic
    }
    else if (bold)
    {
        style_code = "\x1b[1m"; // Bold
    }
    else if (italic)
    {
        style_code = "\x1b[3m"; // Italic
    }

    // Print the formatted string
    printf("%s%s%s%s%s", style_code, color_code, str, ANSI_COLOR_RESET, style_code);
}