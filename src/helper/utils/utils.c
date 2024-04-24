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