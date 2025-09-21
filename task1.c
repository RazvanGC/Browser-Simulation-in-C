#include "task1.h"
#include "binary_tree.h"
#include "min_heap.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
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

int compare(const void *a, const void *b)
{
	node *node1 = *(node **)a;
	node *node2 = *(node **)b;
	satelite *sat1 = node1->data;
	satelite *sat2 = node2->data;
	if (sat1->fq < sat2->fq)
		return -1;
	else if (sat1->fq > sat2->fq)
		return 1;
	else
		return strcmp(sat1->name, sat2->name);
}

void task1(FILE *fin, FILE *fout, int task)
{
	int n;
	fscanf(fin, "%d", &n);

	satelite *satelites = malloc(n * sizeof(satelite));
	DIE(!satelites, "malloc satelites");
	heap_t *heap = min_heap_create(n, sizeof(node *), compare);
	DIE(!heap, "malloc heap");

	for (int i = 0; i < n; i++) {
		satelites[i].name = malloc(15 * sizeof(char));
		DIE(!satelites[i].name, "malloc name");
		fscanf(fin, "%d %s", &satelites[i].fq, satelites[i].name);

		node *new_node = create_node(NULL, NULL, &satelites[i]);

		heap_insert(heap, &new_node);
	}

	int size = heap->size;
	while (heap->size > 1) {
		node *left = *(node **)heap_top(heap);
		heap_pop(heap);
		node *right = *(node **)heap_top(heap);
		heap_pop(heap);

		satelite *new_satellite = malloc(sizeof(satelite));
		DIE(!new_satellite, "malloc new_satellite");

		new_satellite->fq = left->data->fq + right->data->fq;

		new_satellite->name =
			malloc(strlen(left->data->name) + strlen(right->data->name) + 1);
		DIE(!new_satellite->name, "malloc new_satellite->name");

		memcpy(new_satellite->name, left->data->name, strlen(left->data->name));
		memcpy(new_satellite->name + strlen(left->data->name),
			   right->data->name, strlen(right->data->name));
		new_satellite->name[strlen(left->data->name) +
							strlen(right->data->name)] = '\0';

		node *parent = create_node(left, right, new_satellite);
		heap_insert(heap, &parent);
		size++;
		free(new_satellite->name);
		free(new_satellite);
	}

	node *root = *(node **)heap_top(heap);
	heap_pop(heap);

	if (task == 1)
		write_bfs(root, fout, n);
	else if (task == 2)
		task2(fin, fout, root);
	else if (task == 3)
		task3(fin, fout, root, size);
	else if (task == 4)
		task4(fin, fout, root);

	free_tree(root);
	heap_free(heap);

	for (int i = 0; i < n; i++)
		free(satelites[i].name);
	free(satelites);
}
