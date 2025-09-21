#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <stdio.h>

typedef struct satelite {
	int fq;
	char *name;
} satelite;

typedef struct node {
	satelite *data;
	struct node *left;
	struct node *right;
} node;

typedef struct {
	node *root;
} binary_tree;

node *create_node(node *sat_left, node *sat_right, satelite *sat_new);
void free_tree(node *root);
void write_bfs(node *root, FILE *fout, int n);

#endif
