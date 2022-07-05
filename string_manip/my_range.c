#include <stdio.h>
#include <stdlib.h>

/* Create a function my_range which returns a malloc'd array of integers.
This integer array should contain all values between min and max.
Min included - max excluded.
If min value is greater or equal to max's value, a null pointer should be returned.
Don't worry about "free", it will be done in our main(). */

int* my_range(int min, int max);

int main(void) {
    int min = 1;
    int max = 4;
    int* arr = my_range(min, max);
    int size = max - min;

    printf("Numbers within range are: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    free(arr);
    return 0;
}

int* my_range(int min, int max)
{
    if(min >= max)
        return NULL;

    int arr_size = max - min;

    int* arr_ptr = (int *)malloc(sizeof(int) * arr_size);
    // always CHECK RETURN VALUE of functions and HANDLE ERROR return values
    if(arr_ptr == NULL) {
        printf("malloc of size %d failed!\n", arr_size);
        exit(1);
    }
    for(int i = 0; i < arr_size; i++) {
        arr_ptr[i] = min + i;
    }
    return arr_ptr;
}
