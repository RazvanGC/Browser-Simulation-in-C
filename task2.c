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

void traverse(node *root, FILE *fout, char *str)
{
	if (!root)
		return;

	node *original_root = root;
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] == '0')
			root = root->left;
		else if (str[i] == '1')
			root = root->right;
		if (!root->left && !root->right) {
			fprintf(fout, "%s ", root->data->name);
			root = original_root;
		}
		i++;
	}
	fprintf(fout, "\n");
}

void task2(FILE *fin, FILE *fout, void *root)
{
	int n;
	fscanf(fin, "%d", &n);
	char str[100];
	for (int i = 0; i < n; i++) {
		fscanf(fin, "%s", str);
		traverse(root, fout, str);
	}
}
