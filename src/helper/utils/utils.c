#include "utils.h"
#include "../../global/global.h"
#include "../../uart/uart.h"

// Compare two strings
boolean is_equal(char *str1, char *str2) {
  // Loop through the strings and compare each character
  while (*str1 && *str2) {
    // Check if the characters are not equal
    if (*str1 != *str2) {
      return 0;
    }
    str1++;
    str2++;
  }

  // Check if both strings have ended simultaneously
  if (*str1 == '\0' && *str2 == '\0') {
    return True;
  }

  return False;
}

// Get the length of the string
int len(const char *str) {
  // Get the length of the string
  int len = 0;

  // Loop through the string until the null terminator is reached
  while (str[len] != '\0') {
    len++;
  }

  return len;
}

// Concatenate two strings
boolean concat(char *dest, const char *src) {
  // Check for null pointers
  if (dest == 0 || src == 0) {
    return False; // Indicates failure
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

  return True; // Indicates success
}

// Copy the source string to the destination string
void copy(char *destination, const char *source) {
  while (*source != '\0') {
    *destination = *source;
    destination++;
    source++;
  }
  *destination = '\0'; // Null-terminate the destination string
}

// Check if the string starts with the prefix
boolean starts_with(char *str, char *prefix) {
  if (str == (char *)0 || prefix == (char *)0 || len(str) < len(prefix))
    return 0;

  // Check if the string starts with the prefix
  while (*prefix) {
    if (*prefix != *str) {
      return False;
    }
    prefix++;
    str++;
  }

  return True;
}

// Convert an integer to a string
void int_to_string(int number, char *result) {
  result[0] = '\0'; // Initialize the string

  // Declare variables
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
}

// Convert an integer to a hexadecimal string
char *hex_to_string(unsigned int number) {
  // Initialize the result buffer
  static char result[MAX_STR_LEN];
  int i = 0;

  // Extract hexadecimal digits from the number and store them in reverse order
  // in the result buffer
  do {
    // Get the least significant digit
    int digit = number % 16;

    // Convert digit to character and store it in the result buffer
    result[i++] = (digit < 10) ? (char)(digit + '0') : (char)(digit - 10 + 'A');

    // Move to the next digit
    number /= 16;
  } while (number != 0);

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

// Convert a string to an integer
int string_to_int(char *charArray) {
  int result = 0; // Initialize the result
  int sign = 1;   // Positive by default

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
      return False;
    }

    // Move to the next character
    charArray++;
  }

  // Apply sign
  result *= sign;

  return result;
}

// Convert a string to a hexadecimal integer
void mac_address_format(unsigned int num1, unsigned int num2,
                        char *mac_address) {
  // Extract bytes from the integers
  unsigned char byte1 = (num1 >> 24) & 0xFF;
  unsigned char byte2 = (num1 >> 16) & 0xFF;
  unsigned char byte3 = (num1 >> 8) & 0xFF;
  unsigned char byte4 = num1 & 0xFF;
  unsigned char byte5 = (num2 >> 8) & 0xFF;
  unsigned char byte6 = num2 & 0xFF;

  // Convert bytes to hexadecimal representation
  mac_address[0] =
      (byte4 >> 4) < 10 ? (byte4 >> 4) + '0' : (byte4 >> 4) - 10 + 'A';
  mac_address[1] =
      (byte4 & 0x0F) < 10 ? (byte4 & 0x0F) + '0' : (byte4 & 0x0F) - 10 + 'A';
  mac_address[2] = ':';
  mac_address[3] =
      (byte3 >> 4) < 10 ? (byte3 >> 4) + '0' : (byte3 >> 4) - 10 + 'A';
  mac_address[4] =
      (byte3 & 0x0F) < 10 ? (byte3 & 0x0F) + '0' : (byte3 & 0x0F) - 10 + 'A';
  mac_address[5] = ':';
  mac_address[6] =
      (byte2 >> 4) < 10 ? (byte2 >> 4) + '0' : (byte2 >> 4) - 10 + 'A';
  mac_address[7] =
      (byte2 & 0x0F) < 10 ? (byte2 & 0x0F) + '0' : (byte2 & 0x0F) - 10 + 'A';
  mac_address[8] = ':';
  mac_address[9] =
      (byte1 >> 4) < 10 ? (byte1 >> 4) + '0' : (byte1 >> 4) - 10 + 'A';
  mac_address[10] =
      (byte1 & 0x0F) < 10 ? (byte1 & 0x0F) + '0' : (byte1 & 0x0F) - 10 + 'A';
  mac_address[11] = ':';
  mac_address[12] =
      (byte6 >> 4) < 10 ? (byte6 >> 4) + '0' : (byte6 >> 4) - 10 + 'A';
  mac_address[13] =
      (byte6 & 0x0F) < 10 ? (byte6 & 0x0F) + '0' : (byte6 & 0x0F) - 10 + 'A';
  mac_address[14] = ':';
  mac_address[15] =
      (byte5 >> 4) < 10 ? (byte5 >> 4) + '0' : (byte5 >> 4) - 10 + 'A';
  mac_address[16] =
      (byte5 & 0x0F) < 10 ? (byte5 & 0x0F) + '0' : (byte5 & 0x0F) - 10 + 'A';
  mac_address[17] = '\0'; // Null-terminate the string
}