#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_list {
   char *str;
   struct s_list *next;
} lnode;

lnode *bubble_sort_alpha(lnode *head, int pos);
int sort(lnode *head, int pos, int swapped);
int longest_str(lnode *head);

lnode *new_elem(lnode *head, char *str);
void print_list(lnode *head);
void swap(lnode *node, lnode *node2);
int my_strlen(char *string);
int my_strcmp(char *s1, char *s2);

int main(void)
{
    lnode *head = NULL;

    head = new_elem(head, "Dir3");
    head = new_elem(head, "Dir1");

    print_list(head);

    int longest = longest_str(head);
    for (int i = 0; i < longest; i++)
    {
        head = bubble_sort_alpha(head, i);
        printf("pre-sort:\n");
        print_list(head);
    }
    
    printf("sorted:\n");
    print_list(head);

    // deallocate(head);
    return 0;
}

lnode *bubble_sort_alpha(lnode *head, int pos)
{
    int swapped;
    lnode *first;
    lnode *last = NULL;
    if (head == NULL) return head;

    do {
        swapped = 0;
        first = head; // on each round, start from the beginning
        while (first->next != last)
        {
            if (pos > 0)
            {
                if (my_strlen(first->str) >= pos && my_strlen(first->next->str) >= pos)
                {
                    // check if char before pos are equal (the chars before must be equal already), then sort
                    if (first->str[pos-1] == (first->next->str[pos-1]))
                        swapped = sort(first, pos, swapped);
                }
            }
            else swapped = sort(first, pos, swapped);
            first = first->next;
        }
        last = first;
    }
    while (swapped);
    return head;
}

int sort(lnode *node, int pos, int swapped)
{
    // compare & swap (first's value will be pushed to the end if smaller)
    /* if (pos == 1 && (node->str[pos] < 'a') && (node->str[pos] >= 'A')) // check only first capital letter 
    {
        if ((node->str[pos] + 32 > (node->next->str[pos]))) // 32 is the offset between capital and normal letters
        { 
            swap(node, node->next);
            swapped = 1;
        }
    } */
    /* else if ((node->next->str[pos] < 'a') && (node->next->str[pos] >= 'A'))
    {
        if ((node->str[pos] > (node->next->str[pos] + 32))) // 32 is the offset between capital and normal letters
        { 
            swap(node, node->next);
            swapped = 1;
        }
    } */
    // else
    // {
        if ((node->str[pos] > node->next->str[pos]) /* && node->next->str[0] >= 'a' */)
        { 
            swap(node, node->next);
            swapped = 1;
        }
    // }
    return swapped;
}

int longest_str(lnode *head)
{
    int len = 0;
    while(head)
    {
        if ((my_strlen(head->str)) > len )
            len = (my_strlen(head->str));
        head = head->next;
    }
    return len;
}

void swap(lnode *node, lnode *node2)
{
    char *temp = node->str;
    node->str = node2->str;
    node2->str = temp;
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
        printf("%s\n", current->str);
        current = current->next;
    }
}

int my_strlen(char *string)
{
    int counter = 0;
    while (string[counter] != '\0')
        counter++;
    return counter;
}

int my_strcmp(char *s1, char *s2)
{
    while (*s1)
    {
        // if characters differ, or end of the second string is reached
        if (*s1 != *s2)
            break;

        // move to the next pair of characters
        s1++;
        s2++;
        // return the ASCII difference after converting `char*` to `unsigned char*`
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}   