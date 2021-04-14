#pragma once

#include <stdint.h>
#include <stddef.h>

struct HeapSegHdr
{
    size_t length;
    HeapSegHdr *next;
    HeapSegHdr *last;
    bool free;
    void CombineForward();
    void CombineBackward();
    HeapSegHdr *Split(size_t splitLength);
};

void InitializeHeap(void *heapAddress, size_t pageCount);
void ExpandHeap(size_t length);
void free(void *address);
void *malloc(size_t size);