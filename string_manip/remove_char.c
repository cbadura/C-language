#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_char(char *str, char garbage);
void remove_chars(char *str, char garbage);

int main(void)
{
    char* str = malloc(strlen("abcdef")+1);
    strcpy(str, "abcdef");

    remove_chars(str, 'b');
    printf("%s", str);

    free(str);
    return 0;
}

void remove_char(char *str, char garbage)
{
    char *src, *dst;
    for (src = str, dst = str; *src != '\0'; src++)
    {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

void remove_chars(char *str, char c)
{
    int writer = 0, reader = 0;

    while (str[reader])
    {
        if (str[reader] != c) 
            str[writer++] = str[reader];
        reader++;       
    }

    str[writer] = '\0';
}