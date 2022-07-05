/* Write a function called alpha_mirror that takes a string and return a new string built
from this string after replacing each alphabetical character by the opposite alphabetical
character.

'a' becomes 'z', 'Z' becomes 'A'
'd' becomes 'w', 'M' becomes 'N' */

#include <stdio.h>
#include <stdlib.h>

char *alpha_mirror(char* str);
int my_strlen(char* string);
int my_isalpha(char letter);

int main(void)
{
    char str[] = "My horse is Amazing.";
    char *result = alpha_mirror(str);

    printf("Result is: %s\n", result);
    free(result);
    return 0;
}

char *alpha_mirror(char* str)
{
    int len = my_strlen(str);
    char *mirror = malloc(sizeof(char) * (len + 1));

    int offset = 0;
    int i = 0;
    while (str[i] != '\0')
    {        
        if (my_isalpha(str[i]) == 1)
        {
            if (str[i] <= 'Z') // 'Z' is 90
            {
                offset = str[i] - 'A'; // ASCII: 65 is 'A'
                mirror[i] = (char)'Z' - offset;
            }
            if (str[i] >= 'a')
            {
                offset = str[i] - 'a';
                mirror[i] = (char)'z' - offset;
            }
        }
        else
            mirror[i] = str[i];
        i++;
    }
    return mirror;
}

int my_strlen(char *string)
{
    int counter = 0;
    while(string[counter] != '\0')
        counter++;    
    return counter;
}

int my_isalpha(char letter)
{
    if (letter >= 'A' && letter <= 'z')
        return 1;
    return 0;
}

