#include <stdio.h>
#include <stdlib.h>

void print_first_last(int x);
void print_middle(int x);

int main(int ac, char **av)
{
    if (ac == 3)
    {
        int x = atoi(av[1]);
        int y = atoi(av[2]);

        // iterate through lines, print square
        int lineCount = 1;
        while (lineCount <= y)
        {
            if (lineCount == 1 || lineCount == y)
                print_first_last(x);

            else if (lineCount > 1 && lineCount < y)
                print_middle(x);
            
            lineCount++;
        }
    }
    return 0;
}

void print_first_last(int x)
{
    int colCount = 1;
    while (colCount <= x)
    {
        // horizontal border lines
        if (colCount > 1 && colCount <= x - 1)
            printf("-");
        // corners
        if (colCount == 1 || colCount == x)
            printf("o");

        colCount++;
    }
    printf("\n");
}

void print_middle(int x)
{
    int colCount = 1;
    while (colCount <= x)
    {
        // space inside square
        if (colCount > 1 && colCount <= x - 1)
            printf(" ");
        // vertical border lines
        if (colCount == 1 || colCount == x)
            printf("|");
        // jump to next line after reaching right side
        if (colCount == x)
            printf("\n");

        colCount++;
    }
}