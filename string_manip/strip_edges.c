#include <stdio.h>
#include <stdlib.h>

char *strip_edges(char *str);
int my_strlen(char *string);

int main(void)
{
    char str[] = "   Que la lumiere soit   ";

    char *strip = strip_edges(str);
    printf("The new string: %s\n", strip);
    
    free(strip);
    return 0;
}

char *strip_edges(char *str)
{
    if (*str == '\0') return str;

    int len = my_strlen(str); // no +1 because use is different here
    char *stripped = (char*)malloc(sizeof(char) * len);

    int i;
    int start = 0;
    int end = 0;
    // set starting point of the string to after the last initial space
    for (i = 0; str[i] == 32; i++)
        start++;
    // set ending point of the string to last char
    for (i = len-1; str[i] == 32; i--) 
        end++;
    end = len - end-1; // -1 because end hasn't stepped further than the first space at the end of the str
    // copy only the stripped part
    int j = 0;
    for (i = start; i <= end; i++)
    {
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