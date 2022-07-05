/* Write a function that takes two strings and return, without doubles, the
characters that appear in both strings, in the order they appear in the first one. */
#include <stdio.h>
#include <stdlib.h>

char *my_inter(char *strOne, char *strTwo);
void remove_chars(char *str, char garbage);
int my_string_index(char *haystack, char needle);
int my_strlen(char *string);

int main(void)
{
    char str[] = "ddf6vewg64f";
    char strTwo[] = "gtwthgdwthdwfteewhrtag6h4ffdhsd";

    char *unified = my_inter(str, strTwo);
    printf("The string of duplicates is: %s\n", unified);

    free(unified);
    return 0;
}

char *my_inter(char *strOne, char *strTwo)
{
    // put the two strings into an array 
    char* strings[2];
    strings[0] = strOne;
    strings[1] = strTwo;
    
    // create new string for the duplicate chars
    int size = my_strlen(strOne) + my_strlen(strTwo);
    char *dupArr = malloc(sizeof(char) * (size + 1));
    dupArr[size] = '\0'; // to avoid heap buf overflow
    
    // find the unique chars and store them
    int u = 0;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; strings[i][j] != '\0'; j++)
        {
        // 1. for each char in joined, check if char already in uniqArray 
        if(my_string_index(dupArr, strings[i][j]) != -1)
            continue;
        // 2. if not, put the current char at the appropriate position in unique array and increment u
        dupArr[u] = strings[i][j];
        u++;
        }
    }
    dupArr[u] = '\0'; // to avoid filling the rest of the string with junk

    for(int i = 0; dupArr[i] != '\0'; i++)
    {
        // check if any of the unique chars is absent in 1st input string and if so, remove it
        if(my_string_index(strOne, dupArr[i]) == -1)
        {
            remove_chars(dupArr, dupArr[i]);
            i = 0;
        }
    }
    for(int i = 0; dupArr[i] != '\0'; i++)
    {
        // check if any of the unique chars is absent in 2nd input string and if so, remove it
        if(my_string_index(strTwo, dupArr[i]) == -1)
        {
            remove_chars(dupArr, dupArr[i]);
            i = 0;
        }
    }

    return dupArr;
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

int my_string_index(char *haystack, char needle)
{   
    int i = 0;
    while(haystack[i] != '\0') {
        if(haystack[i] == needle)
            return i;
        i++;
    }
    return -1;
}

int my_strlen(char* string)
{
    int counter = 0;
    while(string[counter] != '\0')
        counter++;    
    return counter;
}