#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#include <stdio.h>

typedef struct {
	char *arr;
	int size;
	int capacity;
	size_t data_size;
	int (*cmp)(const void *a, const void *b);
} heap_t;

heap_t *min_heap_create(int capacity, size_t data_size,
						int (*compare)(const void *, const void *));
void heap_insert(heap_t *heap, void *data);
void *heap_top(heap_t *heap);
void heap_pop(heap_t *heap);
int heap_empty(heap_t *heap);
void heap_free(heap_t *heap);

#endif
