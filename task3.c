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

typedef struct {
	char name[15];
	char code[100];
} sat_code;

void generate_codes(node *root, char *current_code, sat_code *codes, int *idx)
{
	if (!root)
		return;

	if (!root->left && !root->right) {
		memcpy(codes[*idx].name, root->data->name, strlen(root->data->name));
		codes[*idx].name[strlen(root->data->name)] = '\0';
		memcpy(codes[*idx].code, current_code, strlen(current_code));
		codes[*idx].code[strlen(current_code)] = '\0';
		(*idx)++;
		return;
	}

	char left_code[1000], right_code[1000];
	//strncpy(left_code, current_code, sizeof(left_code));
	memcpy(left_code, current_code, sizeof(left_code));
	left_code[strlen(current_code)] = '0';
	left_code[strlen(current_code) + 1] = '\0';
	generate_codes(root->left, left_code, codes, idx);

	//strncpy(right_code, current_code, sizeof(right_code));
	memcpy(right_code, current_code, sizeof(right_code));
	right_code[strlen(current_code)] = '1';
	right_code[strlen(current_code) + 1] = '\0';
	generate_codes(root->right, right_code, codes, idx);
}

char *find_code(sat_code *codes, int n, char *name)
{
	for (int i = 0; i < n; i++)
		if (strcmp(codes[i].name, name) == 0)
			return codes[i].code;
	return NULL;
}

void task3(FILE *fin, FILE *fout, void *root, int size)
{
	int n;
	fscanf(fin, "%d", &n);

	// sat_code *codes = malloc(n * sizeof(sat_code));
	sat_code *codes = malloc(size * sizeof(sat_code));
	DIE(!codes, "malloc codes");
	int idx = 0;
	generate_codes((node *)root, "", codes, &idx);

	for (int i = 0; i < n; i++) {
		char name[15];
		fscanf(fin, "%s", name);

		char *code = find_code(codes, idx, name);
		fprintf(fout, "%s", code);
	}
	fprintf(fout, "\n");

	free(codes);
}
