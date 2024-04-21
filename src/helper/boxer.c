// // Function to calculate the length of a string
// int string_length(const char *str)
// {
//     int length = 0;
//     while (*str)
//     {
//         length++;
//         str++;
//     }
//     return length;
// }

// void print_in_box(const char *text)
// {
//     printf("┌");
//     for (int i = 0; text[i] != '\0'; i++)
//         printf("─");
//     printf("┐\n");
//     printf("│ %s │\n", text);
//     printf("└");
//     for (int i = 0; text[i] != '\0'; i++)
//         printf("─");
//     printf("┘\n");
// }