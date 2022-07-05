/* Create a function that splits a string of characters depending on a separator.
The second argument is a unique character separator.
The function should return an array which contains a string wrapped between separator.
There cannot be any empty strings in your array. The string given as an argument of the function won't be modifiable. */

#include <stdio.h>
#include <stdlib.h>

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array {
    int size;
    char **array;
} string_array;
#endif

string_array *my_split(char *str, char *sep);
int find_str_num(char *str, char *sep);
int my_strlen(char *string);

int main(void)
{
    char str[] = "After all this time Always said Snape";
    char sep[] = " ";

    string_array *structPtr = my_split(str, sep);

    for (int i = 0; i < structPtr->size-1; i++)
        printf("Content is: %s\n", structPtr->array[i]);

    
    for (int i = 0; i < structPtr->size-1; i++)
        free(structPtr->array[i]); 
    free(structPtr->array);
    free(structPtr);
    return 0;
}

string_array *my_split(char *str, char *sep)
{
    // set up the struct that will be returned
    string_array *structPtr;
    structPtr = malloc(sizeof(string_array));
    if (structPtr == NULL)
        printf("Error\n");

    // find how many separated strings there will be
    int size = find_str_num(str, sep);
    structPtr->size = size + 1;
    structPtr->array = (char**)malloc(sizeof(char*) * size);

    // if input is empty
    if (*str == '\0' && *sep == '\0')
    {
        structPtr->size = 1;
        structPtr->array[0] = str;
        return structPtr;
    }    

    int j;
    int strCount = 0;
    int len = my_strlen(str) + 1;

    // go through input string, malloc space for each output string and assign chars till sep is hit
    for (int i = 0; str[i] != '\0'; i++)
    {   
        structPtr->array[strCount] = (char*)malloc(sizeof(char) * len);
        for (j = 0; str[i] != *sep && str[i] != '\0'; j++)
        {
            structPtr->array[strCount][j] = str[i];
            i++;
        }
        structPtr->array[strCount][j] = '\0';
        strCount++;
    }
    return structPtr;
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


// other solution
/* string_array* my_split(char* str, char* sep)
{
    // if str is NULL return 0
    if(my_strlen(str) == 0) return 0;
    
    // counts how many string in that array will be for size
    int countSep = 0;
    for(int i = 0; str[i] != '\0'; i++)
        if(str[i] == sep[0]) countSep++;
    
    // Defining an array
    string_array* sepArray = malloc(sizeof(string_array));
    sepArray->size = countSep+1;
    sepArray->array = malloc(sizeof(string_array)*sepArray->size);
    for(int i = 0; i < sepArray->size;i++)
        sepArray->array[i] = malloc(sizeof(string_array)*my_strlen(str));
    

    // checking sep and assigning it to the array
    int index = 0, pos = 0;
    for(int i = 0 ; str[i] != '\0'; i++){
        if(str[i] == sep[0]){
            sepArray->array[index][pos]= '\0';
            index++;
            pos = 0;
        } else {
            sepArray->array[index][pos]= str[i];
            printf("str: %c\n",  sepArray->array[index][pos]);
            pos++;
        }
    }
    return sepArray;
} */