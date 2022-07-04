/* Program to convert a number stored as integer to string
containing the characters that display the number's digits. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
 
char* my_itoa(int num);
char* reverse_string(char *word);
int my_strlen(char* string);

int main(void)
{
    int num = 23;
    char* numStr = my_itoa(num);
    
    int i = 0;
    while (numStr[i] != '\0')
    {
        putchar(numStr[i]); // printf wasn't allowed in the project
        i++;
    }

    free(numStr);
    putchar('\n');
    return 0;
}

char* my_itoa(int num)
{
    // find number of digits
    int len = 0;
    long numCopy = num;
    do {
        len++;
        numCopy /= 10;  // for decimal nbrs
    } while (numCopy != 0);

    char* str = malloc(sizeof(int) * len);
    int i = 0;
    bool isNegative = false;
 
    // handle 0 explicitly, otherwise empty string is printed for 0
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // in standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if(num < 0)
    {
        isNegative = true;
        num = -num;
    }
 
    // process individual digits
    while (num != 0)
    {
        int rem = num % 10;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/10;
    }
 
    // if number is negative, append '-'
    if(isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // append string terminator
 
    // reverse the string
    reverse_string(str);
    return str;
}

char *reverse_string(char *word)
{
    int length, c;
    char *begin, *end;
    
    length = my_strlen(word);
    begin  = word;  // gives begin the same address as word
    end    = word;  // gives end the same address as word
    
    for(c = 0; c < length - 1; c++)
        end++;          // -1 because the last cell contains the

    for(c = 0; c < length/2; c++) // if odd number, the middle letter stays the same  
    {      
        char temp;
        temp   = *end;     
        *end   = *begin;   
        *begin = temp;
    
        begin++;
        end--;
    }
    return word;
}

int my_strlen(char* string) // accept address of string (first element of the array), store it in pointer
{
    int counter = 0;

    while(string[counter] != '\0')
        counter++;    

    return counter;
}