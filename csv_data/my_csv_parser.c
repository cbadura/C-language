/* CSV: it's a 2d array: row and column.
Rows are separated by "line" (the character "\n") and columns are separated by ",". (Separator can be different, it can also be ";")
-> transform a string following the CSV format to a 2d array (array of array).
Your function will take two arguments, the content of a CSV as a string and a separator.
Your function will return an array (lines) of arrays (columns). */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array {
    int size;
    char **array;
} string_array;
#endif

#ifndef STRUCT_STRING_ARRAY_ARRAY
#define STRUCT_STRING_ARRAY_ARRAY
typedef struct s_string_array_array {
    int size;
    string_array **strArr;
} string_array_array;
#endif

string_array_array *my_csv_parser(char* str, char* sep);

int main(void)
{
    /* char doubleArr[2][4][1] = {
        { "a", "b", "c", "e" },
        { "1", "2", "3", "4" },
    }; */

    /// testing/practice
    // set up the array of str arrays

    /* char *input[4] = {
         "a", "b", "c", "e"
    };
    string_array *arr = malloc(sizeof(string_array));
    arr->size = sizeof(input) / sizeof(input[0]);
    arr->array = input;

    char *input2[4] = {
         "1", "2", "3", "4" 
    };
    string_array *arr2 = malloc(sizeof(string_array));
    arr2->size = sizeof(input2) / sizeof(input2[0]);
    arr2->array = input2;

    string_array_array *test = malloc(sizeof(string_array_array));
    test->size = 2;
    test->strArr = malloc(sizeof(string_array) * test->size);
    test->strArr[0] = arr;
    test->strArr[1] = arr2; */
    
    // printf("strArr: %s\n", test->strArr[1]->array[3]);

    string_array_array *result = my_csv_parser("a,b,c,e\n1,2,3,4\n", ",");

    for (int i = 0; i < result->size; i++)
    {
        for (int j = 0; j < result->strArr[i]->size; j++)
            printf("str: %s\n", result->strArr[i]->array[j]);
    }

    // free everything in loops
    return 0;
}

string_array_array *my_csv_parser(char* str, char* sep)
{   
    // find size (how many str arrays there will be) by checking the \n separators
    int size = 0;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '\n') size++;

    // set up the array of str arrays
    string_array_array *result = malloc(sizeof(string_array_array));
    result->size = size;
    result->strArr = malloc(sizeof(string_array) * result->size);
    
    // set up the str arrays, find size (how many strs there will be)
    string_array *arr = malloc(sizeof(string_array));
    string_array *arr2 = malloc(sizeof(string_array));
    int strings = 0;
    for (int i = 0; str[i] != '\n'; i++)
        if (str[i] == *sep) strings++;


    arr->size = strings + 1; // e.g. three commas, four strings
    arr->array = malloc(sizeof(char*) * (arr->size + 1)); // for NULL
    arr2->size = strings + 1;
    arr2->array = malloc(sizeof(char*) * (arr->size + 1));

    // make the individual strs, copy them into str array, then copy these into the arr of arrs
    int i = 0;
    int j = 0;
    // int sepCount = 0;
    for (; str[i] != '\n'; i++)
    {   
        if (str[i] == *sep) i++;
        arr->array[j] = malloc(sizeof(char*) * 2);        
        arr->array[j][0] = str[i];
        arr->array[j][1] = '\0';
        j++;
    }
    i++;
    j = 0;
    // sepCount = 0;
    for (; str[i] != '\n'; i++)
    {   
        if (str[i] == *sep) i++;
        arr2->array[j] = malloc(sizeof(char*) * 2);        
        arr2->array[j][0] = str[i];
        arr2->array[j][1] = '\0';
        j++;
    }
    result->strArr[0] = arr;
    result->strArr[1] = arr2;

    return result;
}