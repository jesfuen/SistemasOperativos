#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// Devuelve un puntero que usa malloc(), hay que liberar esa memoria al final
char *
duplicatepath()
{
	char *dup_path;
	char *path;

	path = getenv("PATH");
	if (path == NULL) {
		fprintf(stderr, "error: getenv PATH");
		exit(EXIT_FAILURE);
	}
	dup_path = strdup(path);
	return dup_path;
}

char *
longuest_path(char *str)
{
	char *token = NULL, *p;
	char *saveptr;
	int count = 0, n = 0;

	p = strtok_r(str, ":", &saveptr);

	count = strlen(p);

	if (n < count) {
		n = count;
		token = p;
	}

	while (p != NULL) {
		p = strtok_r(NULL, ":", &saveptr);

		if (p == NULL)
			break;

		count = strlen(p);

		if (n < count) {
			n = count;
			token = p;
		}
	}

	return token;
}

char *
shortest_path(char *str)
{
	int maxlength = 0, n = 0, count = 0;
	char *token = NULL, *p;
	char *saveptr;

	maxlength = strlen(str);
	n = maxlength;

	p = strtok_r(str, ":", &saveptr);

	count = strlen(p);

	if (n > count) {
		n = count;
		token = p;
	}

	while (p != NULL) {
		p = strtok_r(NULL, ":", &saveptr);

		if (p == NULL)
			break;

		count = strlen(p);

		if (n > count) {
			n = count;
			token = p;
		}
	}

	return token;
}

int
main(int argc, char *argv[])
{

	char *endptr = duplicatepath();
	char *token;

	if (argc > 2) {
		fprintf(stderr, "usage: %s [-s]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (argc == 2 && strcmp(argv[1], "-s") != 0) {
		fprintf(stderr, "usage: %s [-s]\n", argv[0]);
		exit(EXIT_FAILURE);
	} else if (argc == 2 && strcmp(argv[1], "-s") == 0) {
		token = shortest_path(endptr);
		printf("%s\n", token);
	} else {
		token = longuest_path(endptr);
		printf("%s\n", token);
	}

	free(endptr);
	exit(EXIT_SUCCESS);
}
