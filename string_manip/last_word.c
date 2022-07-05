/* Write a program that takes a string and displays its last word followed by a .
A word is a section of string delimited by spaces/tabs or by the start/end of
the string. */

#include <stdio.h>
#include <stdlib.h>

char *last_word(char* str);
int my_isalpha(char letter);
int my_strlen(char *string);

int main(void)
{
    char str[] = "  lorem,ipsum erstwhile  ";

    char *last = last_word(str);
    printf("Last word is: %s\n", last);
    free(last);
    return 0;
}

char *last_word(char *str)
{
    int i, j, curLen;
    int len = my_strlen(str);
    char *last = malloc(sizeof(char) * (len + 1));
    
    i = 0;
    curLen = 0;
    while (str[i] != '\0')
    {
        j = 0;
        while (str[i] != ' ' && my_isalpha(str[i]) == 1)
        {
            last[j] = str[i];
            i++;
            j++;
            curLen = j; 
        }
        if (str[i] != '\0')
            i++;
    }
    last[curLen] = '\0';
    return last;
}

int my_isalpha(char letter)
{
    if (letter >= 'A' && letter <= 'z')
        return 1;
    return 0;
}

int my_strlen(char *string)
{
    int counter = 0;

    while(string[counter] != '\0')
        counter++;
        
    return counter;
}

// alternate version (recursion)
/* #include <ctype.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *find_word(char *str, size_t index)
{
  if(index == 0)
  {
    str[index] = '\0';
    return str; 
  }

  if(!(isalpha(*str)))
  {
    *str = '\0';
    if(isalpha(*(str + 1)))
        return str + 1;
  }

  return find_word(--str, --index);
}

char* last_word(char* input)
{
   if(input[0] == '\0')
     return input;

   size_t index = (strlen(input) - 1);
   return find_word(&input[index], index);
} */