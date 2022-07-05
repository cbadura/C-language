#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *my_downcase(char *expr)
{
    const char OFFSET = 'a' - 'A';  // ASCII lowCase letters come after upCase letters: 'a' - 'A': 97 - 65 = 32
    
    char* word = expr;
    while(*word != '\0')
    {
        if(*word >= 'A' && *word <= 'Z')
            *word += OFFSET;        // this time add difference because we're going down the ASCII table
        *word++;
    }
    return expr;
}

int main()
{
  char *my_str = strdup("AbcE Fgef1"); // tries to allocate enough memory to hold the old string (plus a '\0' character) 
                                       // if allocation worked, copy ("duplicate") old string to new string, return the new address 
  printf("RANDOM CASE -> %s\n", my_str);
  printf("DOWNCASE    -> %s\n", my_downcase(my_str));
  free(my_str);
  return 0;
}