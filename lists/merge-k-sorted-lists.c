/* Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity. */

#include <stdio.h>
#include <stdlib.h>

#ifndef STRUCT_LISTNODE
#define STRUCT_LISTNODE
typedef struct s_listnode {
    int val;
    struct s_listnode* next;
} listnode;
#endif

#ifndef STRUCT_LISTNODE_ARRAY
#define STRUCT_LISTNODE_ARRAY
typedef struct s_listnode_array {
    int size;
    listnode **array;
} listnode_array;
#endif

listnode *merge_k_sorted_lists(listnode_array *arr);
listnode *new_elem(listnode *head, int val);
listnode *concat(listnode *head, listnode *head2);
listnode *bubble_sort(listnode *head);
void swap(listnode *node, listnode *node2);
listnode *mergeList_recur(listnode *a, listnode *b);
void print_list(listnode *head);
void deallocate(listnode *head);

int main(void)
{
    int doubleArr[3][3] = {
        { 1, 4, 5},
        { 1, 3, 4},
        { 2, 6 }
    };
    listnode *head = NULL;
    listnode *head2 = NULL;
    listnode *head3 = NULL;
    
    // store individual arrs of doubleArr in indiv lists
    for (int i = 0; i < 3; i++)
        head = new_elem(head, doubleArr[0][i]);
    for (int i = 0; i < 3; i++)
        head2 = new_elem(head2, doubleArr[1][i]);
    for (int i = 0; i < 3; i++)
        head3 = new_elem(head3, doubleArr[2][i]);

    // store lists in an arr of lists
    listnode *listArr[3] = { 0 };
    listArr[0] = head;
    listArr[1] = head2;
    listArr[2] = head3;
    for (int i = 0; i < 3; i++)
        print_list(listArr[i]);
    // copy the listArr in the list_array struct
    listnode_array *arr = malloc(sizeof(listnode_array));
    arr->size = 3;
    arr->array = listArr;
    //print_list(arr->array[0]);

    listnode *result = NULL;
    result = merge_k_sorted_lists(arr);

    print_list(result);

    /* deallocate(head);
    deallocate(head2);
    deallocate(head3); */

    return 0;
}

listnode* merge_k_sorted_lists(listnode_array *arr)
{
    int i = 0;
    listnode *head = malloc(sizeof(listnode));

    head = arr->array[i];
    for (i = 1; i < arr->size; i++)
        head = concat(head, arr->array[i]);

    head = bubble_sort(head);
    
    // print_list(head);
    return head;
}

listnode *concat(listnode *head, listnode *head2)
{
    if (head == NULL) return head2;
    listnode *cat = malloc(sizeof(listnode));
    cat = head;

    while (head->next)
        head = head->next;
    
    head->next = head2;
    return cat;
}

listnode *bubble_sort(listnode *head)
{
    int swapped;
    listnode *first;
    listnode *last = NULL;
  
    if (head == NULL)
        return head;
  
    do {
        swapped = 0;
        // on each round, start from the beginning
        first = head;
  
        while (first->next != last)
        {
            // compare & swap (first's val will be pushed to the end if smaller)
            if (first->val > first->next->val)
            { 
                swap(first, first->next);
                swapped = 1;
            }
            // advance through list
            first = first->next;
        }
        // when first has reached last, make it the new last element (but before what have been previous last elements)
        last = first;
    }
    while (swapped);  // finish if no swapping is needed anymore

    return head;
}
  
void swap(listnode *node, listnode *node2)
{
    int temp = node->val;
    node->val = node2->val;
    node2->val = temp;
}

listnode *new_elem(listnode *head, int val)
{
    listnode *new = malloc(sizeof(listnode));
    listnode *tmp = head;

    new->next = NULL; // new is always going to be the last element, at this point also the first
    new->val = val;
    if (!head)
        return new;

    while (head->next)      // this is the crucial statement: while head->next != NULL, thus while there is a next element
        head = head->next;  // going down llist: the addr of head (the leftmost element) will be moved one step further right one at a time

    head->next = new;   // new is put as the last element which head->next points to

    return tmp;
}

listnode *mergeList_recur(listnode *a, listnode *b)
{
    listnode* result = NULL;
    /* Base cases */
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;
    /* Pick either a or b, and recur */
    if (a->val <= b->val) {
        result = a;
        result->next = mergeList(a->next, b);
    }
    else {
        result = b;
        result->next = mergeList(a, b->next);
    }
    return result;
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