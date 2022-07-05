#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_list {
   int value;
   struct s_list *next;
} t_list;

t_list *new_elem(t_list *head, int value);
void print_list(t_list *head);
bool check_sorted(t_list *head);
t_list *bubble_sort(t_list *head);
void swap(t_list *node, t_list *node2);
t_list *concat(t_list *head, t_list *head2);
t_list *merge(t_list *head, t_list *head2);
void deallocate(t_list *head);

int main(void)
{
    t_list *head = NULL;
    t_list *head2 = NULL;
    t_list *cat = NULL;

    for (int i = 10; i < 60; i += 10)
        head = new_elem(head, i);

    for (int i = 5; i < 55; i += 10)
        head2 = new_elem(head2, i);

    print_list(head);
    print_list(head2);

    cat = concat(head, head2);
    /* bool sorted = check_sorted(head);

    printf("Is the list sorted? %s\n", sorted ? "true" : "false"); */
    // remove_node(head, 1);
    // print_list(head);
    print_list(cat);

    cat = bubble_sort(cat);
    printf("merged list: \n");
    print_list(cat);

    deallocate(head);
    // deallocate(head2);

    return 0;
}

t_list *new_elem(t_list *head, int value)
{
    t_list *new = malloc(sizeof(t_list));
    t_list *tmp = head;

    new->next = NULL; // new is always going to be the last element, at this point also the first
    new->value = value;
    if (!head)
        return new;

    while (head->next)      // this is the crucial statement: while head->next != NULL, thus while there is a next element
        head = head->next;  // iterate = going down llist: the addr of head (the leftmost element) will be moved one step further right one at a time

    head->next = new;   // new is put as the last element which head->next points to

    return tmp;
}

bool check_sorted(t_list *head)
{
    int x = -1;  // min value for 2 byte int
    t_list *curr = malloc(sizeof(t_list));
    curr = head;

    while (curr)
    {
        if (curr->value < x)
            return false;
        x = curr->value;
        curr = curr->next;
    }
    return true;
}

t_list *concat(t_list *head, t_list *head2)
{
    t_list *third = malloc(sizeof(t_list));
    third = head;

    while (head->next)
        head = head->next;
    
    head->next = head2;
    return third;
}

t_list *bubble_sort(t_list *head)
{
    int swapped;
    t_list *first;
    t_list *last = NULL;
  
    if (head == NULL)
        return head;
  
    do {
        swapped = 0;
        // on each round, start from the beginning
        first = head;
  
        while (first->next != last)
        {
            // compare & swap (first's value will be pushed to the end if smaller)
            if (first->value > first->next->value)
            { 
                swap(first, first->next);
                swapped = 1;
            }
            // advance through list
            first = first->next;
        }
        print_list(first);
        // when first has reached last, make it the new last element (but before what have been previous last elements)
        last = first;
    }
    while (swapped);  // finish if no swapping is needed anymore

    return head;
}
  
void swap(t_list *node, t_list *node2)
{
    int temp = node->value;
    node->value = node2->value;
    node2->value = temp;
}

// merge also means sorting between the two
t_list *merge(t_list *head, t_list *head2)
{
    t_list *third = malloc(sizeof(t_list));
    t_list *last;

    if (head->value < head2->value)
    {
        printf("FIRST IF\n");
        third = last = head;
        head = head->next;
        third->next = NULL;
    }
    else
    {
        third = last = head2;
        head2 = head2->next;
        third->next = NULL;
    }
    while (head && head2)
    {
        printf("INSIDE WHILE\n");
        if (head->value < head2->value)
        {
            last->next = head;
            head = head->next;
            last->next = NULL;
        }
        else
        {
            last->next = head2;
            head2 = head2->next;
            last->next = NULL;
        }
    }
    if (head) last->next = head;
    if (head2) last->next = head2;

    return third;
}

void print_list(t_list *head)
{
    t_list *current = head;
    while (current != NULL)
    {
        printf("%d - ", current->value);
        current = current->next;
    }
    printf("\n");

    /* for (t_list *current = head; current != NULL; current = current->next)
        printf("%d\n", current->value); */
}

void deallocate(t_list *head)
{   
    t_list *curr = head;
    while (curr->next != NULL)
    {
        t_list *temp = curr;
        curr = curr->next;
        free(temp);
    }
    head = NULL;
}