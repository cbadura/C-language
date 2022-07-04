#include <stdio.h>
#include <stdlib.h>
// added for 2nd solution:
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>

void my_cat(char *filename);

int main(int ac, char **av)
{
    if(ac >= 2 && av[1] != NULL)
    {
        for(int i = 1; i < ac; i++)
            my_cat(av[i]);
    }
    return 0;
}

void my_cat(char *filename)
{
    FILE* fptr;
    char c;

    fptr = fopen(filename,"r");
    if(fptr == NULL) {
        printf("Error!");   
        exit(1);             
    }

    while((c = fgetc(fptr)) != EOF) {
        putchar(c);
    }
    fclose(fptr);
    putchar('\n');
}

/*
*** ALTERNATE VERSION ***

int my_cat(char *arg)
{
    char buffer[50 + 1];
    int readBytes;
    int fd;

    if ((fd = open(arg, O_RDONLY)) == -1)
    {
        printf("Error!");
        return -1;
    }

    while ((readBytes = read(fd, buffer, 1)) > 0)
    {
        buffer[readBytes] = '\0';
        printf("%s", buffer);
    }

    close(fd);
} */