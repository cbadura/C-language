/* Given two strings as parameters, create a function able to tell whether or
not the first string is an anagram of the second.

You have to find an optimized solution which will run in O(sa + sb) time (where sa is the length of a and sb length of b).
Our tested string will always be a sequence of ascii characters between 32 and 126 inclusive.
The bigger test we will do is on 2 sequences of 1.000.000 characteres each. It should run in less than 2 seconds. */

#include <stdio.h>
#include <stdlib.h>

int is_anagram(char* strOne, char* strTwo);

int main(void)
{
    char str[] = "iceman";
    char strTwo[] = "cinema";

    int result = is_anagram(str, strTwo);
    printf("The result is: %d\n", result);

    return 0;
}

int is_anagram(char* strOne, char* strTwo)
{
    const int OFFSET = 126 - 32 + 1; // inclusive; 32 in ASCII is space, 126 is 'V'
    int setOne[OFFSET] = { 0 };
    int setTwo[OFFSET] = { 0 };

    /* int i = 0;            // for some compilers (C99?) this instead of the above init is necessary,
                            // otherwise: "variable-sized object may not be initialized" & "excess elements in array initializer"
    for(; i < OFFSET ; i++)
    {
        setOne[i] = 0; 
        setTwo[i] = 0; 
    }

    i = 0; */

    int i = 0;
    while (strOne[i] != '\0')
    {
        setOne[strOne[i] - 32]++;
        i++;
    }
    i = 0;
    while (strTwo[i] != '\0')
    {
        setTwo[strTwo[i] - 32]++;
        i++;
    }

    i = 0;
    while (i < OFFSET)
    {
        if (setOne[i] != setTwo[i])
            return 0;
        i++;
    }
    return 1; 
}