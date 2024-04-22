#include "../global/global.h"
#include "../helper/styler/styler.c"
#include "../helper/utils/utils.h"

int main()
{
    char *text = "Hello, World!";
    char *formatted_text = str_format(text, COLOR.RED, 1);
    printf("%s\n", formatted_text);
    return 0;
}