/* Write a function that takes a string, and returns another string which contains exactly one
space between words, with no spaces or tabs either at the beginning or the end.

A "word" is defined as a part of a string delimited either by spaces/tabs, or
by the start/end of the string. */

#include <stdio.h>
#include <stdlib.h>

char* my_strip(char *str);
int my_strlen(char *string);

int main(void)
{
    char str[] = " this        time it      will     be    more complex  . ";

    char *stripped = my_strip(str);

    printf("%s\n", stripped);  // "this time it will be more complex ."
    return 0;
}

char *my_strip(char *str)
{
    if (*str == '\0') return str;

    int len = my_strlen(str) + 1;
    char *stripped = (char*)malloc(sizeof(char) * len);

    int i = 0;
    int j = 0;
    for (; str[i] != '\0'; i++)
    {
        // if (str[i] == 9)         // ASCII 9 is horizontal tab
        if (str[i] == 32 && str[i + 1] == 32)  // for more than one space, don't copy next space
            continue;
        if (str[i] == 32 && j == 0) // don't copy a space if at the beginning of the new str
            continue;
        if (str[i] == 32 && str[i + 1] == '\0') // don't copy a space at the end
            continue;
        stripped[j] = str[i];
        j++;
    } 
    stripped[j] = '\0';

    return stripped;
}

int my_strlen(char *string)
{
    int counter = 0;
    while (string[counter] != '\0')
        counter++;
    return counter;
}