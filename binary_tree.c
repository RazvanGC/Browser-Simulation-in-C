#include "binary_tree.h"
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

char *my_strdup(const char *s)
{
	char *dup = malloc(strlen(s) + 1);
	if (dup)
		memcpy(dup, s, strlen(s) + 1);
	return dup;
}

node *create_node(node *sat_left, node *sat_right, satelite *sat_new)
{
	node *new_node = malloc(sizeof(node));
	DIE(!new_node, "malloc new_node");

	new_node->data = malloc(sizeof(satelite));
	DIE(!new_node->data, "malloc new_node->data");

	new_node->data->fq = sat_new->fq;
	new_node->data->name = my_strdup(sat_new->name);
	DIE(!new_node->data->name, "strdup name");

	new_node->left = sat_left;
	new_node->right = sat_right;

	return new_node;
}

void free_tree(node *root)
{
	if (!root)
		return;

	free_tree(root->left);
	free_tree(root->right);

	free(root->data->name);
	free(root->data);
	free(root);
}

void write_bfs(node *root, FILE *fout, int n)
{
	if (!root)
		return;

	node **queue = malloc(2 * n * sizeof(node *));
	DIE(!queue, "malloc queue");

	int front = 0, rear = 0;
	queue[rear++] = root;

	while (front < rear) {
		int level_size = rear - front;

		for (int i = 0; i < level_size; i++) {
			node *current = queue[front++];
			fprintf(fout, "%d-%s", current->data->fq, current->data->name);
			if (current->left)
				queue[rear++] = current->left;
			if (current->right)
				queue[rear++] = current->right;
		}
		fprintf(fout, "\n");
	}
	free(queue);
}
