#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <sys/types.h>

enum {
	Maxline = 1024,
};

void
usage()
{
	errx(EXIT_FAILURE, "usage: maxtab file");
}

int
main(int argc, char *argv[])
{

	FILE *f;
	char str[Maxline];
	char buf[Maxline];
	int max = 0;
	int i;
	int n;

	if (argc != 2) {
		usage();
	}
	if ((f = fopen(argv[1], "r")) == NULL) {
		err(EXIT_FAILURE, "%s open error.", argv[1]);
	}

	while (fgets(str, Maxline, f) != NULL) {
		n = 0;

		for (i = 0; i < strlen(str); i++) {
			if (str[i] == '\t') {
				n += 1;
			}
		}

		if (n >= max) {
			max = n;
			strcpy(buf, str);
		}
	}

	printf("%d:%s", max, buf);
	fclose(f);
	exit(EXIT_SUCCESS);

}
