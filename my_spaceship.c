/* You must create a function that takes in a flight path of a rocket ship as a string of letters
and returns the following format: "{x: X, y: Y, direction: 'DIRECTION'}";
X,Y represent the ending coordinates of your ship and direction represents its final direction.
Commands: 'R', turn right; 'L', turn left; 'A', advance. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_spaceship(char *instruction);
char *turn_left(char *direction);
char *turn_right(char *direction);

int main(void)
{
    char* instruction = "RAALALL";

    printf("Final direction is: %s", my_spaceship(instruction));
    return 0;
}

char *my_spaceship(char *instruction)
{
    char *direction;
    char *buffer = (char*)malloc(sizeof(char) * 100);
    int coordinates[2];
    
    direction = "up";
    coordinates[0] = 0;
    coordinates[1] = 0;

    int index = 0;
    while (index < strlen(instruction))     // parse directions here; in a for loop an "i < strlen(instruction) + 1"
    {                                       //  would be necessary to execute the loop at least once
        if (instruction[index] == 'R')
            direction = turn_right(direction);

        else if (instruction[index] == 'L')
            direction = turn_left(direction);
        
        else if (instruction[index] == 'A')
        {   
            if (strcmp(direction, "up") == 0)        
                coordinates[1]--;

            else if (strcmp(direction, "right") == 0)
                coordinates[0]++;

            else if (strcmp(direction, "down") == 0)
                coordinates[1]++;
            
            else
                coordinates[0]--;
        }
        index++;
    }
    snprintf(buffer, 50, "{x: %d, y: %d, direction: '%s'}\n", coordinates[0], coordinates[1], direction);
    return buffer;
}

char *turn_right(char *direction)
{
    char* actDir = (char*)malloc(sizeof(char) * 6);    
    
    if (strcmp(direction, "up") == 0)
        actDir = "right";

    else if (strcmp(direction, "right") == 0)
        actDir = "down";

    else if (strcmp(direction, "down") == 0)
        actDir = "left";
    
    else
        actDir = "up";
    
    return actDir;
}
    
char *turn_left(char *direction)
{
    char* actDir = (char*)malloc(sizeof(char) * 6);

    if (strcmp(direction, "up") == 0)
        actDir = "left";
    
    else if (strcmp(direction, "left") == 0)
        actDir = "down";

    else if (strcmp(direction, "down") == 0)
        actDir = "right";

    else
        actDir = "up";
    
    return actDir;
}