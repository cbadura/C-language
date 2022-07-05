#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
} *first = NULL;

void create(int A[],int n);
void display(struct Node *p);
void recursiveDisplay(struct Node *p);
void reverseDisplay(struct Node *p);

int main(void)
{
    int A[] = { 3, 5, 7, 10, 25, 8, 32, 2 };
    create(A, 8);

    display(first);
    printf("\n");

    recursiveDisplay(first);
    printf("\n");

    reverseDisplay(first);
    printf("\n");

    return 0;
}

void create(int A[],int n)
{
    int i;
    struct Node *temp, *last;

    first = (struct Node *)malloc(sizeof(struct Node));
    first->data = A[0];
    first->next = NULL;
    last = first;

    for(i = 1; i < n; i++)
    {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = A[i];
        temp->next = NULL;
        last->next = temp;
        last = temp;
    }
}

void display(struct Node *p)
{
    while(p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}

void recursiveDisplay(struct Node *p)
{
    if(p != NULL)
    {
        printf("%d ", p->data);
        recursiveDisplay(p->next);
    }
}

void reverseDisplay(struct Node *p)
{
    if(p != NULL)
    {
        rDisplay(p->next);
        printf("%d ", p->data);
    }
}