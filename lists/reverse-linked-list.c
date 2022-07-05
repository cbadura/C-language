// Reverse a singly linked list.

#include <stdio.h>
#include <stdlib.h>

#ifndef STRUCT_LISTNODE
#define STRUCT_LISTNODE
typedef struct s_listnode {
    int val;
    struct s_listnode* next;
} listnode;
#endif

listnode* reverse_linked_list(listnode* head);
listnode *create(int A[],int n);
void print_list(listnode *head);

int main(void)
{
    listnode *head = NULL;
    int arr[] = { 3, 5, 7, 10 };

    head = create(arr, 4);
    print_list(head);

    head = reverse_linked_list(head);
    print_list(head);

    return 0;
}

listnode *reverse_linked_list(listnode* head)
{
    listnode *previous, *after, *current;     // iterative approach
    previous = NULL;
    after = NULL;

    current = head;

    while(current)
    {
        after = current->next; // Before changing next of current, store it in after node 
        current->next = previous; // actual reversing happens here
        previous = current; // move previous and current one step forward 
        current = after;
    }
    head = previous;

    return head;
}

listnode *create(int A[],int n)
{
    int i;
    listnode *head, *temp, *last;

    head = (listnode*)malloc(sizeof(listnode));
    head->val = A[0];
    head->next = NULL;
    last = head;

    for(i = 1; i < n; i++)
    {
        temp = (listnode*)malloc(sizeof(listnode));
        temp->val = A[i];
        temp->next = NULL;
        last->next = temp;
        last = temp;
    }
    return head;
}

void print_list(listnode *head)
{
    listnode *current = head;

    while (current != NULL)
    {
        printf("%d ", current->val);
        current = current->next;   // same statement as in line 40
    }
}

