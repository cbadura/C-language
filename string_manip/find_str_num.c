// In a longer string, find the number of separate strings separated by a separator.

#include <stdio.h>

int find_str_num(char *str, char *sep);

int main(void)
{
    char str[] = "abc def gh-!";
    char sep[] = "-";

    int strNum = find_str_num(str, sep);
    printf("strNum is: %d\n", strNum);

    return 0;
}

int find_str_num(char *str, char *sep)
{
    int strNum = 0;
    if (str && *str != '\0')
        strNum = 1;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == *sep && str[i+1] != '\0')
            strNum++;
    }
    return strNum;
}