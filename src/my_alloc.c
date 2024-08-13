#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "my_alloc.h"

bool initialised_heap = false;

struct block_metadata *heap_start;

void init_heap()
{
    heap_start = sbrk(sizeof(struct block_metadata));
    heap_start->in_use = true;
    heap_start->size = sizeof(struct block_metadata);
    heap_start->next = NULL;
    heap_start->metadata_end = sizeof(struct block_metadata) + heap_start;
}

void debug_print_metadata(struct block_metadata *addr)
{
    printf("size: %d\n in_use %d\n metadata_end %p\n block_addr %p\n next %p\n",
            addr->size, addr->in_use, addr->metadata_end, addr, addr->next);
}

void *my_alloc(int size)
{
    if (initialised_heap == false)
    {
        init_heap();
        initialised_heap = true;
    }

    int block_count = 0;
    struct block_metadata *curr = heap_start;

    while(curr->next != NULL && (curr->in_use == true || size < curr->size + sizeof(struct block_metadata)) )
    {
        printf("(%d): searching block at %p\n", block_count, curr);
        curr = curr->next;
        block_count++;
    }

    printf("\n\nfound at %d\n\n", block_count);

    // if we hit the last block device
    if (curr->next == NULL)
    {
        // end of block including variables are:
        // heap_start->size + heap_start->metadata_end
        int new_block_size = size + sizeof(struct block_metadata);
        struct block_metadata *new_block = sbrk(new_block_size);
        new_block->in_use = true;
        new_block->size = new_block_size;
        new_block->next = NULL;
        new_block->metadata_end = sizeof(struct block_metadata) + new_block;

        // if first item on heap
        if (curr == heap_start) {
            curr = heap_start;
        }
        curr->next = new_block;

        return new_block->metadata_end;
    }


    // this is to check if we have freed a block device before break point
    // we can cut it up again OR we can give them the entire block device and say its in use
    if (curr->in_use == false && curr->size >= size + sizeof(struct block_metadata))
    {
        // check if the block has enough space to store sizeof(struct block_metadata) when cut up
        
    }
}

void my_free(void *ptr)
{
    struct block_metadata *curr = heap_start;
    int block_count = 0;
    while (curr != NULL && curr->metadata_end != ptr)
    {
        debug_print_metadata(curr);
        curr = curr->next;
        block_count++;
    }

    if (curr == NULL)
    {
        printf("cannot free a non block\n");
        return;
    }

    curr->in_use = false;
    printf("successfully freed %p\n", ptr);
}
