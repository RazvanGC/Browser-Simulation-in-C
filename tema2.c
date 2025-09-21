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

int main(int argc, char *argv[])
{
	DIE(argc != 4, "Usage: ./tema2 [-c1 |-c2 |-c3 |-c4 |-c5] [fisier_intrare] "
				   "[fisier_iesire]");

	FILE *fin = fopen(argv[2], "r");
	DIE(!fin, "fopen");
	FILE *fout = fopen(argv[3], "w");
	DIE(!fout, "fopen");

	char *task = argv[1];
	if (strcmp(task, "-c1") == 0) {
		// Call function for task 1
		task1(fin, fout, 1);
	} else if (strcmp(task, "-c2") == 0) {
		// Call function for task 2
		task1(fin, fout, 2);
	} else if (strcmp(task, "-c3") == 0) {
		// Call function for task 3
		task1(fin, fout, 3);
	} else if (strcmp(task, "-c4") == 0) {
		// Call function for task 4
		task1(fin, fout, 4);
	} else if (strcmp(task, "-c5") == 0) {
		// Call function for task 5
	} else {
		fprintf(stderr, "Invalid task: %s\n", task);
	}

	fclose(fin);
	fclose(fout);
	return 0;
}
