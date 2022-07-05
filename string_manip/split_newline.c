// https://codegolf.stackexchange.com/questions/16479/how-do-i-split-a-string-help-plz-code-trolling

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STRING_ARRAY
#define STRING_ARRAY
typedef struct s_string_array {
    int size;
    char **array;
} string_array;
#endif

string_array *split_newline(char *str, char *sep);
int find_str_num(char *str, char *sep);
char *my_strcpy(char *dst, char *src);
int my_strlen(char *string);

int main(void)
{
    char buffer[14]; /* actual length 13 */
    char pattern[3]; /* actual length 2 */

    my_strcpy(buffer, "foo\nbar\nbaz");
    my_strcpy(pattern, "\n");

    /* final newline and return 0 for success! */
    putc(10, stdout); 
    return 0;
}

string_array *split_newline(char *str, char *sep)
{
    string_array *structPtr;
    structPtr = malloc(sizeof(string_array));
    if (structPtr == NULL)
        printf("Error\n");

    // find how many separated strings there will be
    int size = find_str_num(str, sep);
    structPtr->size = size + 1;
    structPtr->array = (char**)malloc(sizeof(char*) * size);
    
    int i = 0;
    while (i < my_strlen(str))
    {
        if (1 == strncmp(str + i, sep, 2))
        {
            /* We matched a backslash char followed by n */
            /* Use syscall for output ASCII 10 */
            putc(10, stdout);
            /* bump index by 2 to skip both backslash and n */
            i += 2;
        } else
        {
            /* This position didn't match the pattern for a newline */
            /* Print character with printf */
            printf("%c", str[i]);
            /* bump index by 1 to go to next matchable position */
            i += 1;
        }
    }
    return structPtr;
}

char *my_strcpy(char *dst, char *src)
{
    int i = 0;
    while(src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = src[i]; // just to copy the '\0' as well
    return dst;
}

int find_str_num(char *str, char *sep)
{
    int strNum = 0;
    if (str && *str != '\0')
        strNum = 1;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == *sep && str[i + 1] != '\0')
            strNum++;
    }
    return strNum;
}

int my_strlen(char *string)
{
    int counter = 0;
    while (string[counter] != '\0')
        counter++;
    return counter;
}