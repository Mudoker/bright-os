#ifndef STYLER_H
#define STYLER_H

#define MAX_ROWS 20
#define MAX_COLS 5

void str_format(char *str, const char *color_code);
void print_in_box(char *str);
void tabulate(char *keys[], int numKeys, char *values[][MAX_ROWS],
              int numValues);
#endif