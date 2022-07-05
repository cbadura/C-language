/* Create a function that creates a t_list element, assigns the value inside of the t_list
element and links the node to the end of the list given as a parameter.
Bonus: You can then create a function to print the list and a function to free it. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_list
{
   int value;
   struct s_list *next;
} t_list;

t_list *new_elem(t_list *head, int value);
void insert_end(t_list** head, int value);
void insert_start(t_list** head, int value);
t_list* insert_after(t_list *node, int value);
t_list *remove_nth_node(t_list* head, int n);
int remove_node(t_list *head, int n);
void print_list(t_list *head);
bool check_sorted(t_list *head);
t_list *concat(t_list *head, t_list *head2);
t_list *merge(t_list *head, t_list *head2);
void deallocate(t_list *head);
int my_list_length(t_list* head);

int main(void)
{
    t_list *head = NULL;
    t_list *head2 = NULL;
    t_list *merged = NULL;

    for (int i = 10; i < 60; i+=10)
        head = new_elem(head, i);

    for (int i = 5; i < 55; i+=10)
        head2 = new_elem(head2, i);

    print_list(head);
    print_list(head2);

    merged = merge(head, head2);
    /* bool sorted = check_sorted(head);

    printf("Is the list sorted? %s\n", sorted ? "true" : "false"); */
    // remove_node(head, 1);
    // print_list(head);
    print_list(merged);

    // deallocate(head);
    // deallocate(head2);

    return 0;
}

t_list *new_elem(t_list *head, int value)
{
    t_list *new = malloc(sizeof(t_list));
    t_list *tmp = head;

    new->next = NULL; // new is always going to be the last element, at this point also the first
    new->value = value;
    /* if string:
    new->s = malloc(sizeof(char) * strlen(s) + 1);
    strcpy(new->s, s);
    */

    if (!head)
        return new;

    while (head->next)      // this is the crucial statement: while head->next != NULL, thus while there is a next element
        head = head->next;  // iterate = going down llist: the addr of head (the leftmost element) will be moved one step further right one at a time

    head->next = new;   // new is put as the last element which head->next points to

    return tmp;
}

void insert_end(t_list** head, int value)
{
    t_list *newNode = malloc(sizeof(t_list));
    if (newNode == NULL)
        exit(1);
    
    newNode->next = NULL;
    newNode->value = value;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    t_list *curr = *head;
    while (curr->next != NULL)
        curr = curr->next;

    curr->next = newNode;
}

/* void insert_start(t_list** head, int value)
{
    t_list *newNode = malloc(sizeof(t_list));
    if (newNode == NULL)
        exit(1);

    newNode->value = value;
    newNode->next = head;

    *head = newNode;
} */

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

t_list* insertNode(int key)
{
   t_list* temp = malloc(sizeof(t_list));
   temp->value = key;
   temp->next = NULL;
   return temp;
}

t_list* insert_after(t_list *node, int value)
{
    t_list* newNode = malloc(sizeof(t_list));
    if (newNode == NULL)
        exit(1);

    newNode->value = value;
    newNode->next = node->next;
    node->next = newNode;
    
    return node;
}

t_list *remove_nth_node(t_list *head, int n)
{
    t_list *temp = head;
    int i;                    
    if (n == 0)
    {
        printf("Element deleted is : %d\n",temp->value);
        head = head->next;        // Advancing the head pointer
        temp->next = NULL;
        free(temp);             // Node is deleted
    }
    else
    {
        for (i = 0; i < n - 1; i++) // -1 because the ptr must point to the element before the one that need to be del
        {
            temp = temp->next;
        }
        
        t_list *del = temp->next;       // del pointer points to the node to be deleted
        temp->next = temp->next->next;
        printf("Element deleted is : %d\n",del->value);      
        del->next = NULL;
        free(del);                          // Node is deleted
    }
    return head;
}

// another one that returns the deleted value
int remove_node(t_list *head, int n)
{
    t_list *prev = malloc(sizeof(t_list));
    int x = -1; // this will store the deleted value

    // check if n is valid
    if (n < 1 || n > my_list_length(head))
        return -1;

    // delete
    // handle special case of deleting first node
    if (n == 1)
    {
        prev = head;
        x = head->value;
        head = head->next;
        free(prev);
        return x;
    }
    // in all other cases
    else
    {
        for (int i = 0; i < n - 1; i++) // moving to the right node: -1 because we stop at the node before the node to be deleted
        {
            prev = head;
            head = head->next;
        }
        // actual deletion here
        prev->next = head->next;
        x = head->value;
        free(head);
    }

    return x;
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

int my_list_length(t_list *head)
{
    // count size of list and return
    int count = 0;
    t_list *current = malloc(sizeof(t_list));
    current = head;
    while (current)
    {
        current = current->next;
        count++;
    }
    return count;
}

