int is_equal(char *str1, char *str2);
int concat(char *dest, const char *src);
int len(const char *str);
void copy(char *dest, const char *src);
int starts_with(char *str, char *prefix);
void int_to_string(int num, char *result);
int string_to_int(char *str);
void mac_address_format(unsigned int num1, unsigned int num2,
                        char *mac_address);
char *hex_to_string(unsigned int num);