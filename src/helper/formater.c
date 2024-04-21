// #include "../global/headers/format.h"

// int strings_are_equal(const char *str1, const char *str2)
// {
//     while (*str1 && *str2)
//     {
//         if (*str1 != *str2)
//         {
//             return 0; // Not equal
//         }
//         str1++;
//         str2++;
//     }
//     // Check if both strings have ended simultaneously
//     if (*str1 == '\0' && *str2 == '\0')
//     {
//         return 1; // Equal
//     }
//     return 0; // Not equal
// }

// // Function to format string with color and print it
// void format_and_print(char *str, const char *color, int bold, int italic)
// {
//     char *color_code = "";
//     char *style_code = "";

//     // Assign color code based on the provided color string
//     if (strings_are_equal(color, "red"))
//     {
//         color_code = "\x1b[31m"; // Red
//     }
//     else if (strings_are_equal(color, "green"))
//     {
//         color_code = "\x1b[32m"; // Green
//     }
//     else if (strings_are_equal(color, "yellow"))
//     {
//         color_code = "\x1b[33m"; // Yellow
//     }
//     else if (strings_are_equal(color, "blue"))
//     {
//         color_code = "\x1b[34m"; // Blue
//     }
//     else if (strings_are_equal(color, "magenta"))
//     {
//         color_code = "\x1b[35m"; // Magenta
//     }
//     else if (strings_are_equal(color, "cyan"))
//     {
//         color_code = "\x1b[36m"; // Cyan
//     }
//     else
//     {
//         color_code = ANSI_COLOR_RESET; // Default color
//     }

//     // Assign style code based on bold and italic flags
//     if (bold && italic)
//     {
//         style_code = "\x1b[1;3m"; // Bold and Italic
//     }
//     else if (bold)
//     {
//         style_code = "\x1b[1m"; // Bold
//     }
//     else if (italic)
//     {
//         style_code = "\x1b[3m"; // Italic
//     }

//     // Print the formatted string
//     printf("%s%s%s%s%s", style_code, color_code, str, ANSI_COLOR_RESET, style_code);
// }