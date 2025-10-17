#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	--argc;

	if (argc % 2 != 0) {
		fprintf(stderr,"error: bad number of arguments\n");
		exit(EXIT_FAILURE);
	}

	

	exit(EXIT_SUCCESS);
}