/* Given a sorted linked list, delete all duplicates such that each elements appear only once. */

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

listnode *remove_duplicates_from_sorted_list(listnode* head);
listnode *new_elem(listnode *head, int value);
void print_list(listnode *head);
void deallocate(listnode *head);

int main(void)
{
    listnode *head = NULL;
    int arr[] = { 3, 5, 5, 7 };
    int arrLen = sizeof arr / sizeof arr[0];

    for (int i = 0; i < arrLen; i++)
        head = new_elem(head, arr[i]);

    print_list(head);

    head = remove_duplicates_from_sorted_list(head);

    print_list(head);
    deallocate(head);
    return 0;
}

listnode *remove_duplicates_from_sorted_list(listnode* head)
{
    // iterate through list, compare curr value with all the others in the list and remove element if they match
    listnode *curr = head;
    listnode *after = NULL;
    
    if (curr == NULL)
        return head;

    while (curr->next)
    {
        // compare current node's value with next node's
        if (curr->val == curr->next->val)
        {          
            after = curr->next->next;  // jump over the node containing duplicate
            free(curr->next);
            curr->next = after;     // assign the new ptr to curr->next ptr 
        }
        else    // only advance if no deletion
        {
            curr = curr->next;
        }
    }
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