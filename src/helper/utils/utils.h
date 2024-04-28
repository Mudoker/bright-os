#include "../../global/struct.h"

// Function prototypes
boolean is_equal(char *str1, char *str2);    // Check if two strings are equal
boolean concat(char *dest, const char *src); // Concatenate two strings
int len(const char *str);                    // Get the length of a string
void copy(char *dest, const char *src);      // Copy a string
boolean starts_with(char *str,
                    char *prefix); // Check if a string starts with a prefix
void int_to_string(int num, char *result); // Convert an integer to a string
int string_to_int(char *str);              // Convert a string to an integer
void mac_address_format(unsigned int num1, unsigned int num2,
                        char *mac_address); // Format MAC address
char *
hex_to_string(unsigned int num); // Convert a number to a hexadecimal string