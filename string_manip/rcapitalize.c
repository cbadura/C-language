/* Write a function that takes one string and capitalize the last character of each word in uppercase
and the rest in lowercase. A word is a section of string delimited by spaces/tabs or the start/end of the
string. If a word has a single letter, it must be capitalized. A letter is a character in the set [a-zA-Z] */
#include <stdio.h>
#include <stdlib.h>

char *rcapitalize(char *str);
int my_isalpha(char letter);
int my_isblank(char ch);

int main(void)
{
    char str[] = "   But... This iS not THAT COMPLEX";

    char *capitalized = rcapitalize(str);
    printf("The new string is: %s\n", capitalized);

    return 0;
}

char *rcapitalize(char *str)
{
    const char OFFSET = 'a' - 'A';

    int i = 0;
    while (str[i] != '\0') 
    {
        if (my_isalpha(str[i]) == 1)
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] += OFFSET;
            if ((str[i] >= 'a' && str[i] <= 'z') && (my_isblank(str[i + 1]) == 1 || str[i + 1] == '\0'))
                str[i] -= OFFSET;
        }
        i++;
    }
    return str;
}

int my_isalpha(char letter)
{
    if (letter >= 'A' && letter <= 'z')
        return 1;
    else
        return 0;
}

int my_isblank(char ch)
{
    if ((int)ch == 32)
        return 1;
    else
        return 0;
}