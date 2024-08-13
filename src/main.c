#include <stdio.h>
#include <unistd.h>

#include "my_alloc.h"

// malloc takes in a length argument, allocates it to vram and 
// returns a pointer to the front of that block of memory
int main(void)
{
    printf("init myalloc\n\n");

    int *int1 = my_alloc(sizeof(int));
    *int1 = 2;
    int *int2 = my_alloc(sizeof(int));
    *int2 = 4;
    int *int3 = my_alloc(sizeof(int));
    *int3 = 8;

    debug_heap();
    my_free(int1);
    debug_heap();
    my_free(int2);
    my_free(int3);
    debug_heap();


    return 0;
}
