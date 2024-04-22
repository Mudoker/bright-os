#include "os.h"
#include "../global/global.h"
#include "../helper/styler/styler.h"

void os_greet()
{
    char *os_name = OS_INF.ascii_art_name;
    os_name = str_format(os_name, COLOR.YELLOW, 000);
    uart_puts(os_name);
}