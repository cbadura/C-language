/* Write a function my_union that takes two strings and returns, without doubles, the
characters that appear in either one of the strings. */
#include <stdio.h>
#include <stdlib.h>

char *my_union(char* strOne, char* strTwo);
int my_string_index(char *haystack, char needle);
int my_strlen(char *string);

int main(void)
{
    char str[] = "zpadinton";
    char strTwo[] = "paqefwtdjetyiytjneytjoeyjnejeyj";

    char *unified = my_union(str, strTwo);
    printf("The unified str is: %s\n", unified);

    free(unified);
    return 0;
}

char *my_union(char *strOne, char *strTwo)
{
    // put the two strings into an array 
    char* strings[2];
    strings[0] = strOne;
    strings[1] = strTwo;
    
    // create new string for the unique chars
    int size = my_strlen(strOne) + my_strlen(strTwo);
    char *uniqArr = malloc(sizeof(char) * (size + 1)); // max size if both strings contain only uniq chars
    uniqArr[size] = '\0'; // to avoid heap buf overflow
    // find the unique chars and store them
    int u = 0;  // for moving forward in the uniqArr
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; strings[i][j] != '\0'; j++)
        {
        // 1. for each char in joined, check if char already in uniqArray 
        if(my_string_index(uniqArr, strings[i][j]) != -1)
            continue;
        // 2. if not, put the current char at the appropriate position in unique array and increment u
        uniqArr[u] = strings[i][j];
        u++;
        }
    }
    uniqArr[u] = '\0'; // to avoid filling the rest of the string with junk
    return uniqArr;
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