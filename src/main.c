#include <stdio.h>
#include <unistd.h>

#include "my_alloc.h"

/*
 *  TODO:
 *   - [ ] defrag memory blocks
 *   - [ ] make use of freed blocks
 *      - [ ] cut block up to only fit requested size
 */

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

    int *many_ints = my_alloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
    {
        many_ints[i] = i * i * i;
    }

    debug_heap();
    my_free(int1);
    debug_heap();
    my_free(int2);
    my_free(int3);
    debug_heap();


    return 0;
}
