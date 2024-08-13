#ifndef MY_ALLOC_H
#define MY_ALLOC_H

#include <stdbool.h>

struct block_metadata
{
    bool in_use;
    int size;   // size of thhe entire size of the block including the metadata
    struct block_metadata *next;
    struct block_metadata *metadata_end;
};

void *my_alloc(int size);
void init_heap();
void my_free();
void debug_print_metadata(struct block_metadata *ptr);

#endif
