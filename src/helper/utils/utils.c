int strcmp(char *str1, char *str2)
{
    // Compare the strings
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
        {
            return 0;
        }
        str1++;
        str2++;
    }

    // Check if both strings have ended simultaneously
    if (*str1 == '\0' && *str2 == '\0')
    {
        return 1;
    }

    return 0;
}

int strlen(char *str)
{
    // Get the length of the string
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }

    return len;
}

int concat(char *dest, const char *src)
{
    // Get the length of the destination string
    int dest_len = strlen(dest);

    // Concatenate the source string to the destination string to the end
    int i = 0;
    while (src[i] != '\0')
    {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';

    return 1;
}