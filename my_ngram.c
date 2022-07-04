/* My Ngram will take one or multiple strings as arguments.
It will display, one per line, each character and the numbers of times it appears.
Order will be alphanumerical. */

#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE 128

void fill_array(int* arr, int arrSize, char* str);
void print_ngram(int* arr, int arrSize);

int main(int ac, char** av)
{
    int arr[ARR_SIZE] = { 0 };
    
    if (ac >= 2 && av[1] != NULL)
    {
        for (int i = 1; i < ac; i++)
            fill_array(&arr[0], ARR_SIZE, av[i]);
    }
    print_ngram(&arr[0], ARR_SIZE);

    return 0;
}

void fill_array(int* arr, int arrSize, char* str)
{
    int index = 0;
    while (str[index] != '\0')
    {
        for (int i = 0; i < arrSize; i++)
        {
            // increment the list of occurences for the current letter
            if (str[index] == i)
                arr[i]++;
        }
        index++;
    }
}

void print_ngram(int* arr, int arrSize)
{
    for(int i = 0; i < arrSize; i++)
    {
        if(arr[i] > 0)
            printf("%c:%d\n", i, arr[i]);
    }
}