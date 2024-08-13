#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "my_alloc.h"

block *heap_head;
bool heap_initialised = false;

void init_heap()
{
    if (!heap_initialised) 
    { 
        // inits heap_head at the beginning of the heap
        heap_head = sbrk(sizeof(block));

        heap_head->in_use = true;
        heap_head->size = sizeof(block);
        heap_head->next = NULL;
        heap_head->meta_end = heap_head + sizeof(block);

        heap_initialised = true;
    }
}

void debug_heap()
{
    block *curr = heap_head;
    while (curr != NULL)
    {
        if (curr == heap_head)
        {
            fprintf(stderr, ">>> HEAD <<<\n");
        }
        fprintf(stderr, "=== CURRENT BLOCK: %p ===\n", curr);
        fprintf(stderr, "\tsize: %d\n", curr->size);
        fprintf(stderr, "\tin_use: %d\n", curr->in_use);
        fprintf(stderr, "\tnext: %p\n", curr->next);
        fprintf(stderr, "\tmeta_end: %p\n", curr->meta_end);
        fprintf(stderr, "=== END OF BLOCK ===\n\n");

        curr = curr->next;
    }

    fprintf(stderr, ">>>  null! <<<\n");
}

void create_new_block(int size, block *curr, block *new_block)
{
    int new_block_size = sizeof(block) + size;

    new_block->size = new_block_size;
    new_block->in_use = true;
    new_block->meta_end = new_block + sizeof(block);
    new_block->next = NULL;

    curr->next = new_block;
}

void split_block(int alloc_size, block *curr)
{
    // check if size if exactly alloc_size or there isn't enough space to store metadata + alloc size
    if (curr->size == alloc_size + sizeof(block)) {
        curr->in_use = true;
        curr->meta_end = curr + sizeof(block);
        return;
    } else if (curr->size >= alloc_size + sizeof(block)) {
        block *new_block = alloc_size + curr + sizeof(block);
        new_block->next = curr->next;
        new_block->in_use = false;
        new_block->meta_end = new_block + sizeof(block);
        new_block->size = curr->size - alloc_size - sizeof(block);

        curr->next = new_block;
        curr->size = alloc_size + sizeof(block);
        curr->in_use = true;
    }

}

void *my_alloc(int size)
{
    init_heap();
    block *curr = heap_head;
    block *new_block;

    // inits head if not defined
    while (curr->next != NULL)
    {
        if (curr->in_use == false && curr->size >= size + sizeof(block))
        {
            fprintf(stderr, "found a freed block at %p!\n", curr);
            break;
        }
        curr = curr->next;
    }

    // if malloc is called and there are no free previous blocks
    if (curr->next == NULL) {
        new_block = sbrk(sizeof(block) + size);

        create_new_block(size, curr, new_block);
    } else if (curr->in_use == false && curr->size >= size + sizeof(block)) {
        split_block(size, curr);
        new_block = curr;
    } else {
        fprintf(stderr, "wtf???????????????????????????????????????????\n");
    }

    return new_block->meta_end;
}

void defrag()
{
    block *curr = heap_head;
    block *prev = NULL;

    while (curr->next != NULL)
    {
        // never attempt to defrag on heap_head
        if (curr != heap_head && (prev->in_use == false && curr->in_use == false))
        {
            prev->size = prev->size + curr->size;
            prev->next = curr->next;

            curr = prev;
            curr = curr->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

}

void my_free(void *ptr)
{
    block *curr = heap_head;
    while(curr->next != NULL && curr->meta_end != ptr)
    {
        curr = curr->next;
    }

    // user inputted correct ptr to be freed
    if (curr->meta_end == ptr) {
        curr->in_use = false;
        fprintf(stderr, "Free on block %p with data at %p successful!\n", curr, curr->meta_end);
    } else {
        fprintf(stderr, "Failed - check if %p is a my_alloc'd pointer?\n", ptr);
    }

    // defrag connected blocks
    defrag();
}
