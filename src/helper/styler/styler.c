#include "../../global/global.h"
#include "../utils/utils.h"
#include "./styler.h"

// Function to format string with color and print it
char *str_format(const char *str, const char *color_code, int style)
{
    if (str == 0 || color_code == 0)
    {
        return '\0'; // Invalid input
    }

    char *style_code = "";

    // Assign style code based on bold and italic flags
    if (style == 111)
    {
        concat(style_code, STYLER.BOLD_ON);
        concat(style_code, STYLER.ITALIC_ON);
        concat(style_code, STYLER.UNDERLINE_ON);
    }
    else if (style == 1)
    {
        style_code = STYLER.BOLD_ON;
    }
    else if (style == 10)
    {
        style_code = STYLER.ITALIC_ON;
    }
    else if (style == 100)
    {
        style_code = STYLER.UNDERLINE_ON;
    }

    static char formatted_str[MAX_STR_LEN];

    if (formatted_str == '\0')
    {
        return ("Memory allocation failed\n");
    }

    // Concatenate the style code, color code and the string
    concat(formatted_str, style_code);
    concat(formatted_str, color_code);
    concat(formatted_str, str);

    return formatted_str;
}