#include <stdio.h>

char* first_word_cpy(char* dst, char* src);
int my_strlen(char *string);

int main(void)
{
    char dst[100] = { 0 };
    char *src     = "Hello world";
    
    printf("first word -> %s\n", first_word_cpy(dst, src));
    return 0;
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

int my_strlen(char *string)
{
    int counter = 0;
    while (string[counter] != '\0')
        counter++;
        
    return counter;
}