

#ifndef _HEAP_H_
#define _HEAP_H_

#include <orderedList.h>

struct memory_block_s {
	unsigned char allocated;
	unsigned int size; /*< Size of memory block */
	unsigned int *address; /*< Pointer to memory */
};

struct heap_s {
	struct orderedList_t memoryBlocks; /*< ordered list of memory blocks */
	unsigned int baseAddress;
	unsigned int size;
};

struct heap_s *createHeap(unsigned int baseAddr, unsigned int size);

void *heapAlloc(struct heap_s *heap, unsigned int size, unsigned int aligned);
void heapFree(struct heap_s *heap, void *addr);

#endif
