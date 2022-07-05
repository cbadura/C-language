/* Count the size of each elements in an array.
The function receives a string array as parameter and returns an array with the length of each string.
Yes, you have to allocate for the struct AND then to allocate for the array inside it.
Don't forget to set the size. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array {
    int size;
    char** array;
} string_array;
#endif

#ifndef STRUCT_INTEGER_ARRAY
#define STRUCT_INTEGER_ARRAY
typedef struct s_integer_array {
    int size;
    int* array;
} integer_array;
#endif

integer_array *my_count_on_it(string_array *structPtr);
int my_strlen(char *string);

int main(void)
{
    char *strArr[] = { "This", "is", "the", "way" };
    string_array arrStruct = { sizeof strArr / sizeof strArr[0], strArr };

    integer_array *structPtr = my_count_on_it(&arrStruct);

    for (int i = 0; i < structPtr->size; i++)
        printf("The length of string %d is: %d\n", i, structPtr->array[i]);
        
    free(structPtr->array);
    free(structPtr);
    return 0;
}

integer_array *my_count_on_it(string_array *structPtr)
{
    integer_array *intStructPtr = malloc(sizeof(integer_array));
    intStructPtr->array = malloc(structPtr->size * sizeof(int));
    intStructPtr->size = structPtr->size;

    for (int i = 0; i < structPtr->size; i++)
        intStructPtr->array[i] = my_strlen(structPtr->array[i]);

    return intStructPtr;
}

int my_strlen(char *string)
{
    int counter = 0;
    while (string[counter] != '\0')
        counter++;
        
    return counter;
}