/* Create a function that will take an array of string as a parameter and return an array of int containing the length of each element
of the input array. These lengths will be stored in ascending order. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* OrderTheLength(char **strings)
{
    int tmp = 0;
    int size = 0;
    for (int i = 0; strings[i] != NULL; i++)
        size++;

    int *lengths = malloc(sizeof(int) * size);

    for (int i = 0; strings[i] != NULL; i++)
        lengths[i] = strlen(strings[i]);

    int i = 0;
    while (i + 1 < size) // exclude NULL
    {
        if (lengths[i] > lengths[i + 1])
        {
            tmp = lengths[i + 1];
            lengths[i + 1] = lengths[i];
            lengths[i] = tmp;
            i = 0;
        }
        else
            i++;
    }

    return lengths;
}

int main()
{
    char **input = malloc(sizeof(char*) * (3 + 1));
    for (int i = 0; i < 6; i++)
        input[i] = (char*)malloc(sizeof(char) * 50);
    input[0] = "test1";
    input[1] = "testfwefewfest";
    input[2] = "test test";
    input[3] = NULL;
    int *ret = OrderTheLength(input);
    for (int i = 0; i < 3; i++)
        printf("%d ", ret[i]);
}

// char *string = '\0';
