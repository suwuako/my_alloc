#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "my_alloc.h"


int main(int argc, char *argv[])
{
    int *my_int = my_alloc(8);
    *my_int = 42;
    printf("%d is stored in %p\n\n", *my_int, my_int);

    int *my_int2 = my_alloc(8);
    *my_int2 = 2000;
    printf("%d is stored in %p\n\n", *my_int2, my_int2);

    int *my_int3 = my_alloc(8);
    *my_int3 = 192;
    printf("%d is stored in %p\n\n", *my_int3, my_int3);

    int *my_int4 = my_alloc(8);
    *my_int4 = 168;
    printf("%d is stored in %p\n\n", *my_int4, my_int4);

    int *my_int_array = my_alloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
    {
        my_int_array[i] = i * i;
        printf("(%d): %d is stored in %p\n", i, my_int_array[i], &my_int_array[i]);
    }

    int *my_int5 = my_alloc(8);
    *my_int5 = 1;
    printf("%d is stored in %p\n\n", *my_int5, my_int5);

    my_free(my_int_array - 20);
    my_free(my_int_array);

    int *my_int6 = my_alloc(8);
    *my_int6 = 1;
    printf("%d is stored in %p\n\n", *my_int6, my_int6);
    /*
    printf("%d is stored in %p\n\n", *my_int4, my_int4);
    printf("throwback: \n\n");
    printf("%d is stored in %p\n\n", *my_int, my_int);
    printf("%d is stored in %p\n\n", *my_int2, my_int2);
    printf("%d is stored in %p\n\n", *my_int3, my_int3);
    printf("%d is stored in %p\n\n", *my_int4, my_int4);
    */


    return 0;
}
