/* Write a function to rearrange a string so that the first word is moved to the end of the string.
In essence, you take the first word, pick it up, move it to the end of the string while shifting the rest of the string to the front.
Thus, the first word becomes the last, and others stay in the same order.
A word is a section of a string delimited by spaces/tabs or the start/end of the string. */

#include <stdio.h>
#include <stdlib.h>

char *rostring(char* str);
char *strip_edges(char *str);
char *first_word_cpy(char *dst, char *src);
char *finalize(char *dst, char *src);
int my_strlen(char *string);

int main(void)
{
    char str[] = "    Que la      lumiere soit et la lumiere fut    ";

    char *ro = rostring(str);
    printf("The new string: %s\n", ro);
    
    free(ro);
    return 0;
}

char *rostring(char* str)
{
    char *firstWord = (char*)malloc(sizeof(char) * (my_strlen(str) + 1));
    char *temp = (char*)malloc(sizeof(char) * (my_strlen(str) + 1));
    char *final = (char*)malloc(sizeof(char) * (my_strlen(str) + 1));

    // first remove all the excess spaces at the edges
    temp = strip_edges(str);

    // check if there is more than one word; if not, return the stripped str
    int check = 0;
    for (int i = 0; temp[i] != '\0'; i++)
        if (temp[i] == 32) check = 1;
    if (check == 0) return temp;

    // if there is more than one word, copy first word of stripped str into char*
    first_word_cpy(firstWord, temp);

    // finish the string
    final = finalize(temp, firstWord);

    free(firstWord);
    free(temp);
    return final;
}

char *first_word_cpy(char *dst, char *src)
{
    int i = 0;
    while(src[i] != 32)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return dst;
}

char *finalize(char *str, char *first)
{
    int len = my_strlen(str) + 1;
    char *final = (char*)malloc(sizeof(char) * len);
    // first move index of the orig str to after the first space: here final's 1st word will start
    int strInd = 0;
    while(str[strInd] != 32) strInd++;
    strInd++;
    // then copy the rest into the final str, add a space & move index forward by 1
    int finalInd = 0;
    for (; str[strInd] != '\0'; strInd++)
    {
        final[finalInd] = str[strInd];
        finalInd++;
    }
    final[finalInd] = 32;
    finalInd++;
    // copy the first word to the end of final
    for (int i = 0; first[i] != '\0'; i++)
    {
        final[finalInd] = first[i];
        finalInd++;
    }
    final[finalInd] = '\0';
    return final;
}

char *strip_edges(char *str)
{
    if (*str == '\0') return str;

    int len = my_strlen(str); // no +1 because use is different here
    char *stripped = (char*)malloc(sizeof(char) * len);

    int i;
    int start = 0;
    int end = 0;
    // set starting point of the string to after the last initial space
    for (i = 0; str[i] == 32; i++)
        start++;
    // set ending point of the string to last char
    for (i = len-1; str[i] == 32; i--) 
        end++;
    end = len - end-1; // -1 because end hasn't stepped further than the first space at the end of the str
    // copy only the stripped part
    int j = 0;
    for (i = start; i <= end; i++)
    {
        stripped[j] = str[i];
        j++;
    }
    stripped[j] = '\0';
    return stripped;
}

int my_strlen(char *string)
{
    int counter = 0;
    while (string[counter] != '\0')
        counter++;
        
    return counter;
}