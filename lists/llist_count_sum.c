#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
} *first = NULL;

int count(struct Node *p)
{
    int len = 0;
    while(p)
    {
        len++;
        p = p->next;
    }
    return len;   
}

int recurCount(struct Node *p)
{
    if(p != NULL)
        return recurCount(p->next) + 1;
    else
        return 0;
}

int sum(struct Node *p)
{
    int sum = 0;

    while(p != NULL)
    {
        sum += p->data;
        p = p->next;
    }
    
    return sum;
}

int recurSum(struct Node *p)
{
    if(p == NULL)
        return 0;
    else
        return recurSum(p->next) + p->data;
}