#include "../../global/global.h"
#include "../../uart/uart.h"

int is_equal(char *str1, char *str2) {
  // Compare the strings
  while (*str1 && *str2) {
    if (*str1 != *str2) {
      return 0;
    }
    str1++;
    str2++;
  }

  // Check if both strings have ended simultaneously
  if (*str1 == '\0' && *str2 == '\0') {
    return 1;
  }

  return 0;
}

int len(const char *str) {
  // Get the length of the string
  int len = 0;
  while (str[len] != '\0') {
    len++;
  }

  return len;
}

int concat(char *dest, const char *src) {
  // Check for null pointers
  if (dest == 0 || src == 0) {
    return 0; // Indicates failure
  }

  // Get the length of the destination string
  int dest_len = len(dest);

  // Concatenate the source string to the destination string
  int i = 0;
  while (src[i] != '\0') {
    dest[dest_len + i] = src[i];
    i++;
  }
  dest[dest_len + i] = '\0'; // Null-terminate the destination string

  return 1; // Indicates success
}

char *copy(char *destination, const char *source) {
  char *start = destination;
  while (*source != '\0') {
    *destination = *source;
    destination++;
    source++;
  }
  *destination = '\0'; // Null-terminate the destination string
  return start;
}

// Check if the string starts with the prefix
int starts_with(char *str, char *prefix) {
  if (str == (char *)0 || prefix == (char *)0 || len(str) < len(prefix))
    return 0;

  // Check if the string starts with the prefix
  while (*prefix) {
    if (*prefix != *str) {
      return 0;
    }
    prefix++;
    str++;
  }

  return 1;
}

char *int_to_string(int number) {
  static char result[MAX_CMD_SIZE];
  int i = 0;
  int is_negative = 0;

  // Handle negative numbers
  if (number < 0) {
    is_negative = 1;
    number = -number;
  }

  // Extract digits from the number and store them in reverse order in the
  // result buffer
  do {
    result[i++] = (char)(number % 10 + '0');
    number /= 10;
  } while (number != 0);

  // Add '-' sign for negative numbers
  if (is_negative) {
    result[i++] = '-';
  }

  // Reverse the string
  int j;
  char temp;
  for (j = 0; j < i / 2; j++) {
    temp = result[j];
    result[j] = result[i - j - 1];
    result[i - j - 1] = temp;
  }

  // Add null terminator
  result[i] = '\0';

  return result;
}

int string_to_int(char *charArray) {
  int result = 0;
  int sign = 1; // Positive by default

  // Check for negative sign
  if (*charArray == '-') {
    sign = -1;
    charArray++; // Move past the negative sign
  }

  // Iterate through the characters until the null terminator is reached
  while (*charArray != '\0') {
    // Convert character to digit
    int digit = *charArray - '0';

    // Ensure it's a valid digit
    if (digit >= 0 && digit <= 9) {
      result = result * 10 + digit;
    } else {
      // Invalid character encountered
      uart_puts("Error: Invalid character in integer string\n");
      return 0;
    }

    // Move to the next character
    charArray++;
  }

  // Apply sign
  result *= sign;

  return result;
}