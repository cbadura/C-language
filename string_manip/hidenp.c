/* Write a function named hidenp that takes two strings and returns 1
if the first string is hidden in the second one,
otherwise returns 0 followed by a newline.

Let s1 and s2 be strings. We say that s1 is hidden in s2 if it's possible to
find each character from s1 in s2, in the same order as they appear in s1.
Also, the empty string is hidden in any string. */

#include <stdio.h>

int hidenp(char* hidden, char* haystack);
int my_strlen(char *string);
int check_filled_set(int *set, int index);

int main(void)
{
    char str[] = "fgex.;";
    char strTwo[] = "tyf34gdgf;'ektufjhgdgex.;.;rtjynur6";

    int result = hidenp(str, strTwo);
    printf("The result is: %d\n", result);

    return 0;
}

int hidenp(char* hidden, char* haystack)
{
    if (hidden[0] == '\0') return 1;
    
    int len = my_strlen(hidden);
    int hiddenSet[len];

    int i = 0;                                   
    for (; i < len ; i++)
        hiddenSet[i] = 0;
    
    int counter = 0;
    for (int i = 0; haystack[i] != '\0'; i++)
    {
        for (int j = 0; hidden[j] != '\0'; j++)
        {
            if (hidden[j] == haystack[i] && hiddenSet[j] == 0)
            {   
                if (j == 0)
                {   
                    counter++;
                    hiddenSet[j]++;
                }
                if (j != 0 && (check_filled_set(hiddenSet, j) == 1))
                {
                    counter++;
                    hiddenSet[j]++;
                }
            }
        }
    }
    if(counter == len)
        return 1;
    else
        return 0;
}

int check_filled_set(int *set, int index)
{
    if (set[index - 1] == 1)
        return 1;
    else
        return 0;
}

int my_strlen(char *string)
{
    int counter = 0;

    while(string[counter] != '\0')
        counter++;
        
    return counter;
}
