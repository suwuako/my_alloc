#include <stdio.h>
#include <unistd.h>

void *my_alloc(int len)
{
    return sbrk(len);
}

// malloc takes in a length argument, allocates it to vram and 
// returns a pointer to the front of that block of memory
int main(void)
{
    printf("hello, meson\n");
    return 0;
}
