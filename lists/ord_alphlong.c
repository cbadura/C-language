/* Write a function that takes a string as a parameter and returns its words sorted
in order of their length first and then in alphabetical order on each line:
when we say alphabetical order we ignore the case of letters.
For example aA and Aa are the same but the original order must remain
(lower and upper case are the same in alphabetical order). If there are
duplicates, they must remain.
There will be only spaces, tabs and alphanumeric caracters in strings.
You'll have only one space between same size words and ^ otherwise.
A word is a section of string delimited by spaces/tabs or the start/end of the
string. If a word has a single letter, it must be capitalized. */

#include <stdio.h>
#include <stdlib.h>

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array {
    int size;
    char **array;
} string_array;
#endif

#ifndef STRUCT_LISTNODE
#define STRUCT_LISTNODE
typedef struct s_listnode {
    char *str;
    struct s_listnode* next;
} lnode;
#endif

char *ord_alphlong(char *str);
char *make_str_from_list(lnode *head, int len);
lnode *bubble_sort(lnode *head);
lnode *bubble_sort_alph(lnode *head);
void swap(lnode *node, lnode *node2);
string_array *my_split(char *str, char *sep);
int find_str_num(char *str, char *sep);
lnode *new_elem(lnode *head, char *str);
void print_list(lnode *head);
int my_strlen(char *string);
char* my_strcat(char* dest, char* src);

int main(void)
{
    char str[] = "A a b B cc ca cd";

    printf("in order: %s\n", ord_alphlong(str));
    return 0;
}

char *ord_alphlong(char *str)
{
    if (!str || *str == '\0') return str;

    int len = my_strlen(str) + 1;
    char *order = malloc(sizeof(char) * len);

    // split the string and store in str arr
    string_array *arr = my_split(str, " ");

    // then put words into new llist according to length and sort them by length
    lnode *head = NULL;
    for (int i = 0; i < arr->size-1; i++)
        head = new_elem(head, arr->array[i]);

    bubble_sort(head); 
    
    // sort the nodes according to their first letter
    bubble_sort_alph(head);
    print_list(head);

    // put the words back together into one string, groups of same length are marked by ^
    order = make_str_from_list(head, len);
    return order;
}

char *make_str_from_list(lnode *head, int len)
{
    lnode *current = head;
    char *str = malloc(sizeof(char) * len);

    while (current != NULL)
    {
        my_strcat(str, current->str);

        if (current->next)
        {
            if (my_strlen(current->str) < my_strlen(current->next->str))
                my_strcat(str, "^");
            else
                my_strcat(str, " ");
        }
        current = current->next;
    }
    
    str[len-1] = '\0';
    return str;
}

lnode *bubble_sort_alph(lnode *head)
{
    int swapped;
    lnode *first;
    lnode *last = NULL;
  
    if (head == NULL)
        return head;
  
    do {
        swapped = 0;
        // on each round, start from the beginning
        first = head;
        while (first->next != last)
        {
            // compare first letter & swap (first's str will be pushed to the end if smaller)
            while (first->next && (my_strlen(first->str) == my_strlen(first->next->str)))
            {
                if ((first->str[0] > first->next->str[0]) && first->next->str[0] >= 'a')
                {
                    swap(first, first->next);
                    swapped = 1;
                }
                if (first->str[1] && first->next->str[1])
                {
                    if ((first->str[0] == first->next->str[0]) && (first->str[1] > first->next->str[1]))
                    {
                        swap(first, first->next);
                        swapped = 2;
                    }
                }
                first = first->next;
            }
            // advance through list
            if (first->next != last)
                first = first->next;
        }
        if (swapped == 2) break; // this prevents segfault

        // when first has reached last, make it the new last element (but before what have been previous last elements)
        last = first;
    } while (swapped);  // finish if no swapping is needed anymore
    
    return head;
}

lnode *bubble_sort(lnode *head)
{
    int swapped;
    lnode *first;
    lnode *last = NULL;
  
    if (head == NULL)
        return head;
  
    do {
        swapped = 0;
        // on each round, start from the beginning
        first = head;
  
        while (first->next != last)
        {
            // compare & swap (first's str will be pushed to the end if smaller)
            if (my_strlen(first->str) > my_strlen(first->next->str))
            { 
                swap(first, first->next);
                swapped = 1;
            }
            // advance through list
            first = first->next;
        }
        // when first has reached last, make it the new last element (but before what have been previous last elements)
        last = first;
    } while (swapped);  // finish if no swapping is needed anymore
    
    return head;
}
  
void swap(lnode *node, lnode *node2)
{
    char *temp = node->str;
    node->str = node2->str;
    node2->str = temp;
}

string_array *my_split(char *str, char *sep)
{
    // set up the struct that will be returned
    string_array *structPtr;
    structPtr = malloc(sizeof(string_array));
    if (structPtr == NULL)
        printf("Error\n");

    // find how many separated strings there will be
    int size = find_str_num(str, sep);
    structPtr->size = size + 1;
    structPtr->array = (char**)malloc(sizeof(char*) * size);

    // if input is empty
    if (*str == '\0' && *sep == '\0')
    {
        structPtr->size = 1;
        structPtr->array[0] = str;
        return structPtr;
    }    

    int j;
    int strCount = 0;
    int len = my_strlen(str) + 1;

    // go through input string, malloc space for each output string and assign chars till sep is hit
    for (int i = 0; str[i] != '\0'; i++)
    {   
        structPtr->array[strCount] = (char*)malloc(sizeof(char) * len);
        for (j = 0; str[i] != *sep && str[i] != '\0'; j++)
        {
            structPtr->array[strCount][j] = str[i];
            i++;
        }
        structPtr->array[strCount][j] = '\0';
        strCount++;
    }
    return structPtr;
}

int find_str_num(char *str, char *sep)
{
    int strNum = 0;
    if (str && *str != '\0')
        strNum = 1;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == *sep && str[i + 1] != '\0')
            strNum++;
    }
    return strNum;
}

lnode *new_elem(lnode *head, char *str)
{
    lnode *new = malloc(sizeof(lnode));
    lnode *tmp = head;

    new->next = NULL; // new is always going to be the last element, at this point also the first
    new->str = str;
    if (!head)
        return new;

    while (head->next)      // this is the crucial statement: while head->next != NULL, thus while there is a next element
        head = head->next;  // iterate = going down llist: the addr of head (the leftmost element) will be moved one step further right one at a time

    head->next = new;   // new is put as the last element which head->next points to
    return tmp;
}

void print_list(lnode *head)
{
    lnode *current = head;
    while (current != NULL)
    {
        printf("%s - ", current->str);
        current = current->next;
    }
    printf("\n");
}

int my_strlen(char *string)
{
    int counter = 0;
    while (string[counter] != '\0')
        counter++;
    return counter;
}

char* my_strcat(char* dest, char* src)
{
    while(*dest) dest++;
    while((*dest++ = *src++));
    return --dest;
}