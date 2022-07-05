/* Count the elements of a linked list, i.e. return the length of a list.  */

#ifndef STRUCT_LISTNODE
#define STRUCT_LISTNODE
typedef struct s_listnode
{
    int val;
    struct s_listnode* next;
} listnode;
#endif

#include <stdio.h>
#include <stdlib.h>

int my_list_length(listnode* head);
listnode *new_elem(listnode *head, int value);
void print_list(listnode *head);
void deallocate(listnode *head);

int main(void)
{
    listnode *head = NULL;
    int arr[] = { 3, 5, 5, 7 };
    int arrLen = sizeof arr / sizeof arr[0];
    printf("arrLen: %d\n", arrLen);

    for (int i = 0; i < arrLen; i++)
        head = new_elem(head, arr[i]);

    print_list(head);

    int len = my_list_length(head);

    printf("length is: %d\n", len);
    deallocate(head);
    return 0;
}

int my_list_length(listnode* head)
{
    // count size of list and return
    int count = 0;
    listnode *current = malloc(sizeof(listnode));
    current = head;
    while (current)
    {
        current = current->next;
        count++;
    }
    return count;
}

listnode *new_elem(listnode *head, int value)
{
    listnode *new = malloc(sizeof(listnode));
    listnode *tmp = head;

    new->next = NULL; // new is always going to be the last element, at this point also the first
    new->val = value;
    if (!head)
        return new;

    while (head->next)      // this is the crucial statement: while head->next != NULL, thus while there is a next element
        head = head->next;  // going down llist: the addr of head (the leftmost element) will be moved one step further right one at a time

    head->next = new;   // new is put as the last element which head->next points to

    return tmp;
}

void print_list(listnode *head)
{
    listnode *current = head;

    while (current != NULL)
    {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

void deallocate(listnode *head)
{   
    listnode *curr = head;
    while (curr->next != NULL)
    {
        listnode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    head = NULL;
}