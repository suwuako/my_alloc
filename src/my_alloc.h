#ifndef MY_ALLOC_H
#define MY_ALLOC_H

#include <stdbool.h>
#include <unistd.h>

typedef struct metadata_block
{
    bool in_use;
    int size;       // size is including the beginning of metadata + alloc size
    struct metadata_block *next;
    struct metadata_block *meta_end;
} block;

void init_heap();
void debug_heap();
void *my_alloc(int size);
void my_free(void *ptr);


#endif
