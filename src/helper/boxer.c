void print_in_box(const char *text)
{
    printf("┌");
    for (int i = 0; i < strlen(text) + 2; i++)
        printf("─");
    printf("┐\n");
    printf("│ %s │\n", text);
    printf("└");
    for (int i = 0; i < strlen(text) + 2; i++)
        printf("─");
    printf("┘\n");
}