#include <stdio.h>
#include <stdlib.h>

typedef struct s_list {
   char *str;
   long long mtime;
   struct s_list *next;
} lnode;

lnode *sort_same_time_alpha(lnode *head);
lnode *sort_mtime(lnode *head);
void time_swap(lnode *node, lnode *node2);

lnode *new_elem_time(lnode *head, long long time);
void print_list(lnode *head);
void swap(lnode *node, lnode *node2);

int my_strlen(char *string);
int my_strcmp(char *s1, char *s2);
char *my_strdup(char* str);

int main(void)
{
    lnode *head = NULL;

    head = new_elem_time(head, 1651479240);
    head = new_elem_time(head, 1652290215);
    head = new_elem_time(head, 1651658318);
    print_list(head);

    head = sort_mtime(head);
    printf("pre-sorted:\n");
    print_list(head);

    head = sort_same_time_alpha(head);
    printf("sorted:\n");
    print_list(head);

    // deallocate(head);
    return 0;
}

lnode *sort_same_time_alpha(lnode *head)
{
    lnode *timeList = head;
    lnode *first = head;
    char *tmp;

    // bubble sort: two entries of same mtime are sorted alphabetically
    while (head->next != NULL)
    {
        if ((head->next->mtime == head->mtime) && (my_strcmp(head->str, head->next->str) < 0))
        {
            tmp = my_strdup(head->next->str);
            head->next->str = head->str;
            head->str = tmp;
            head = first;
            continue;
        }
        head = head->next;
    }
    // if (tmp[0] != '\0') free(tmp);
    return timeList;
}

lnode *sort_mtime(lnode *head)
{
    int swapped;
    lnode *first;
    lnode *last = NULL;
    if (head == NULL) return head;

    do {
        swapped = 0;
        first = head;
        while (first->next != last)
        {
            // printf("time: %lld - nexttime: %lld\n", first->mtime, first->next->mtime);
            if ((first->mtime < first->next->mtime))
            {
                time_swap(first, first->next);
                swapped = 1;
            }
            first = first->next;
        }
        last = first;
        // print_list(head);
    }
    while (swapped);
    return head;
}

void time_swap(lnode *node, lnode *node2)
{
    long long temp = node->mtime;
    node->mtime = node2->mtime;
    node2->mtime = temp;
}

lnode *new_elem_time(lnode *head, long long time)
{
    lnode *new = malloc(sizeof(lnode));
    lnode *tmp = head;

    new->next = NULL;
    new->mtime = time;
    if (!head)
        return new;

    while (head->next)      
        head = head->next;  

    head->next = new;
    return tmp;
}

void print_list(lnode *head)
{
    lnode *current = head;
    while (current != NULL)
    {
        printf("%lld\n", current->mtime);
        // printf("%s\n", current->str);
        current = current->next;
    }
}

char *my_strdup(char *str)
{
    int size;
    char *dupStr;
    size = my_strlen(str) + 1;

    dupStr = (char*)malloc(sizeof(char) * size);
    if(dupStr == NULL)
    {
        // printf("malloc of size %d failed!\n", size);
        return NULL;
    }
    for(int i = 0; i < size; i++)
        dupStr[i] = str[i];
    dupStr[size-1] = '\0';
    
    /*  while(*str) {       // the same thing
        *ptr++ = *str++;
    }
    *ptr = '\0'; */
    return dupStr;   
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

int my_strlen(char *str)
{
    int counter = 0;
    while(str[counter] != '\0')
        counter++;    
    return counter;
}
