/* Create a function that joins an array of strings on a separator character.
You will receive two parameters, an array with all the strings and a separator.
The function returns a string where all the string from array are joined with the separator. */

#include <stdio.h>
#include <stdlib.h>

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array {
    int size;
    char **array;
} string_array;
#endif

char* my_join(string_array *strings, char *separator);
int get_length_of_strings(string_array *strings);
int my_strcmp(char *s1, char *s2);
char *my_strcpy(char *dst, char *src);
int my_strlen(char *string);

int main(void)
{
    char *strArr[] = { "abc", "def", "gh", "!" };
    char *separator = "blah";
    string_array *arr_struct = malloc(sizeof(arr_struct)); // put the whole arr inside, not just &str_arr[0]
    arr_struct->array = strArr;
    arr_struct->size = 4;

    // char **array  = (char**)malloc(sizeof(char*) * 4 + 1);

    /* int len;
    for (int i = 0; i < 4; i++)
    {
        len = my_strlen(strArr[i]) + 1;
        array[i] = (char*)malloc(sizeof(char) * len);

        my_strcpy(array[i], strArr[i]);
    }
    array[4]= NULL; 
        printf("AFTER MALLOC\n");
    arr_struct->size = 4;
    arr_struct->array = array; */
    
    char *joined = my_join(arr_struct, separator);

    printf("The joined string is: %s\n", joined);
    
    /* for (int i = 0; i < 4; i++)
    {
        free(array[i]);
    }
    free(array) */
    free(joined);
    return 0;
}

char *my_join(string_array *strings, char *separator)
{
    // set up the return string
    int lenStrings, sizeOfJoined, counter;
    char *joined = NULL;

    if (strings->size == 0 && my_strcmp(separator, " ") == 0) return NULL;

    // get length of all the strings for malloc
    lenStrings = get_length_of_strings(strings);
    sizeOfJoined = lenStrings + (strings->size - 1) + 1;
    joined = (char*)malloc(sizeof(char) * sizeOfJoined);

    // for all of the strings, go through them
    counter = 0;
    for (int i = 0; i < strings->size; i++)
    {
        for (int j = 0; j < my_strlen(strings->array[i]); j++)
        { 
            joined[counter] = strings->array[i][j];
            counter++;
        }

        if(i != strings->size - 1)
        {
            for(int h = 0; h < my_strlen(separator); h++)
            {
                joined[counter] = separator[h];
                counter++;
            }
        }
    }
    joined[counter] = '\0';

    return joined;
}

int get_length_of_strings(string_array *strings)
{
    int lengthOfStrings = 0;
    int j;

    for (int i = 0; i < strings->size; i++)
    {    
        j = 0;
        while (strings->array[i][j] != '\0')
        {
            j++;
            lengthOfStrings++;
        }
    }
    return lengthOfStrings;
}

int my_strcmp(char *s1, char *s2)
{
    while(*s1 != '\0' && *s1 == *s2)   // check if 1st str has reached the end & char of 1st str matches char of 2nd
    {
        s1++;                           // if they do, increment both addresses of the strings
        s2++;
    }
    return *s1 - *s2;                   // if all chars match, ASCII values of last matching chars will be subtracted --> 0       
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

int my_strlen(char *string)
{
    int counter = 0;
    while (string[counter] != '\0')
        counter++;
    return counter;
}


/* char* my_join(string_array* strings, char* sep)
{
    char* newChar;
    int size = strings->size;
    int j = 0;
    int index = 0;
    newChar = (char*)malloc(size*sizeof(char*));

    for(int i = 0 ; i < strings->size; i++)
    {
        for(int j = 0; strings->array[i][j]!= '\0'; j++)
        {
            newChar[index] = strings->array[i][j];
            index++;
        }
        for(int z = 0; sep[z] != '\0' &&  i < strings->size-1; z++)
        {
            newChar[index] = sep[z];   
            index++;
        }
    }
    if(strings->size == 0) return 0;
    else return newChar;
} 
  */