#include "binary_tree.h"
#include "min_heap.h"
#include "task1.h"
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

node *lca(node *root, char *name1, char *name2)
{
	if (!root)
		return NULL;
	if (strcmp(root->data->name, name1) == 0 ||
		strcmp(root->data->name, name2) == 0)
		return root;

	node *left = lca(root->left, name1, name2);
	node *right = lca(root->right, name1, name2);

	if (left && right)
		return root;
	return left ? left : right;
}

node *multiple_lca(node *root, char **names, int count)
{
	node *ancestor = lca(root, names[0], names[1]);
	for (int i = 2; i < count; i++)
		ancestor = lca(root, ancestor->data->name, names[i]);

	return ancestor;
}

void task4(FILE *fin, FILE *fout, void *root_void)
{
	node *root = (node *)root_void;
	int n;
	fscanf(fin, "%d", &n);

	char **names = malloc(n * sizeof(char *));
	for (int i = 0; i < n; i++) {
		names[i] = malloc(20);
		fscanf(fin, "%s", names[i]);
	}

	node *ancestor = multiple_lca(root, names, n);
	if (ancestor)
		fprintf(fout, "%s\n", ancestor->data->name);

	for (int i = 0; i < n; i++)
		free(names[i]);
	free(names);
}
