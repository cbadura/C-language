/* Given a linked list, remove the n-th node from the end of list and return its head. */

#include <stdio.h>
#include <stdlib.h>

#ifndef STRUCT_LISTNODE
#define STRUCT_LISTNODE
typedef struct s_listnode
{
    int val;
    struct s_listnode* next;
} listnode;
#endif

listnode *remove_nth_node_from_end_of_list(listnode *head, int n);
listnode *new_elem(listnode *head, int value);
int my_list_length(listnode* head);
void print_list(listnode *head);
void deallocate(listnode *head);

int main(void)
{
    listnode *head = NULL;
    // int arr[] = { 3, 5, 7, 10 };

    for (int i = 1; i < 5; i++)
        head = new_elem(head, i);

    print_list(head);

    head = remove_nth_node_from_end_of_list(head, 2);
    printf("The new list: ");
    print_list(head);

    deallocate(head);
    return 0;
}

listnode *remove_nth_node_from_end_of_list(listnode *head, int n)
{
    // approach: remove (length - (n + 1))th node from the beginning: if length = 4 and n = 2, remove n + 1 = 3rd element
    if (head == NULL)
        return NULL;
    
    // traverse list and count elements
    int count = my_list_length(head);
    // set count to the element before the one to be deleted
    count = count - n;
    if (count == 0)
        return head->next;  // head will be deleted, list will simply start from head's next element
    
    // traverse again with new pointers
    listnode *curr = head;
    listnode *prev = NULL;
    while (count > 0)
    {
        prev = curr;   // (for 1st time:) store head's addr in prev
        curr = curr->next; // (for 1st time:) store head's next elem in head
        count--;
    }
    // before deleting, relink the 'next' pointer of the node to be deleted to its previous node & then set it itself to NULL
    prev->next = curr->next;
    curr->next = NULL;

    free(curr);
    return head;
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