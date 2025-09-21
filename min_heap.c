#include "min_heap.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* useful macro for handling error codes */
#define DIE(assertion, call_description)                                       \
	do {                                                                       \
		if (assertion) {                                                       \
			fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                 \
			perror(call_description);                                          \
			exit(errno);                                                       \
		}                                                                      \
	} while (0)

/* index of the parent */
#define GO_UP(x) (((x) - 1) >> 1)

/* index of the left child */
#define GO_LEFT(x) (((x) << 1) + 1)

/* index of the right child */
#define GO_RIGHT(x) (((x) << 1) + 2)

/* creates a new min-heap */
heap_t *min_heap_create(int capacity, size_t data_size,
						int (*compare)(const void *, const void *))
{
	heap_t *heap = malloc(sizeof(heap_t));
	DIE(!heap, "malloc heap");

	heap->arr = malloc(capacity * data_size);
	DIE(!heap->arr, "malloc array");

	heap->size = 0;
	heap->capacity = capacity;
	heap->data_size = data_size;
	heap->cmp = compare;

	return heap;
}

/* inserts a new element in the heap and fixes the structure */
void heap_insert(heap_t *heap, void *data)
{
	char *arr = heap->arr;
	int pos = heap->size;

	// copy data at the end of the heap
	memcpy(arr + pos * heap->data_size, data, heap->data_size);

	// bubble up (heapify-up)
	while (pos > 0) {
		int p = GO_UP(pos);
		void *child = arr + pos * heap->data_size;
		void *parent = arr + p * heap->data_size;

		if (heap->cmp(parent, child) <= 0)
			break;

		char *tmp = malloc(heap->data_size);
		DIE(!tmp, "malloc tmp");

		memcpy(tmp, parent, heap->data_size);
		memcpy(parent, child, heap->data_size);
		memcpy(child, tmp, heap->data_size);
		free(tmp);

		pos = p;
	}

	heap->size++;

	// resize if needed
	if (heap->size == heap->capacity) {
		heap->capacity *= 2;
		heap->arr = realloc(heap->arr, heap->capacity * heap->data_size);
		DIE(!heap->arr, "heap->arr realloc");
	}
}

/* returns pointer to the top element (min element) */
void *heap_top(heap_t *heap)
{
	if (heap->size <= 0)
		return NULL;

	return (char *)heap->arr;
}

/* removes the top element and fixes the heap structure */
void heap_pop(heap_t *heap)
{
	char *arr = heap->arr;

	// move last element to the root
	if (heap->size > 1)
		memmove(arr, arr + (heap->size - 1) * heap->data_size, heap->data_size);
	heap->size--;

	int pos = 0;
	while (1) {
		int l = GO_LEFT(pos);
		int r = GO_RIGHT(pos);
		int smallest = pos;

		if (l < heap->size && heap->cmp(arr + l * heap->data_size,
										arr + smallest * heap->data_size) < 0)
			smallest = l;

		if (r < heap->size && heap->cmp(arr + r * heap->data_size,
										arr + smallest * heap->data_size) < 0)
			smallest = r;

		if (smallest == pos)
			break;

		char *tmp = malloc(heap->data_size);
		DIE(!tmp, "malloc tmp");

		memcpy(tmp, arr + pos * heap->data_size, heap->data_size);
		memcpy(arr + pos * heap->data_size, arr + smallest * heap->data_size,
			   heap->data_size);
		memcpy(arr + smallest * heap->data_size, tmp, heap->data_size);

		free(tmp);

		pos = smallest;
	}
}

/* checks if the heap is empty */
int heap_empty(heap_t *heap) { return heap->size <= 0; }

/* frees all heap memory */
void heap_free(heap_t *heap)
{
	free(heap->arr);
	free(heap);
}
