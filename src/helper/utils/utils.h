#ifndef UTILS_H
#define UTILS_H

int is_equal(const char *str1, const char *str2);
int concat(char *dest, const char *src);
int len(const char *str);
int copy(char *dest, const char *src);
int starts_with(char *str, char *prefix);
char *int_to_string(int num);
int string_to_int(char *str);

#endif