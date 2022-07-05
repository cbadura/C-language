#include <stdio.h>

int my_strlen(char*);
char* reverse_string(char*); 

int main() {
    char my_str[] = "Hello";
    
    printf("Before reverse -> %s\n", my_str);
    printf("Reverse -> %s\n", reverse_string(my_str)); // array decays into pointer here
    return 0;                                  // compiler automatically converts arr into ptr to its first el
}

char* reverse_string(char *word)
{
    int length, c;
    char *begin, *end;
    
    length = my_strlen(word);
    begin  = word;  // gives begin the same address as word
    end    = word;  // gives end the same address as word
    
    for(c = 0; c < length - 1; c++)
        end++;          // puts the pointer to the address of "o" (-1 because the last cell contains the \0)

    for(c = 0; c < length/2; c++) {      // if odd number, the middle letter stays the same  
        char temp;
        temp   = *end;     // stores the "o" in temp
        *end   = *begin;   // stores the "h" instead of the "o" at end point of word
        *begin = temp;     // stores the "o" at beginning of word's address
    
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