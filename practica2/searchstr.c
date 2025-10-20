#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>

// execl() para ejecutar el comando fgrep -> pasar ruta a fgrep con whereis
// Ruta /usr/bin/fgrep

void
error()
{
	fprintf(stderr,"error: bad number of arguments\n");
	exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
	int i;

	if (argc % 2 == 0) {
		error();
	}
	argc--;
	argv++;

	for (i = 0; i < argc; i += 2)
	{
		switch (fork())
		{
		case  -1:
			err(EXIT_FAILURE, "fork failed");
		
		case 0:
			execl("/bin/fgrep","fgrep", argv[i+1], argv[i], NULL);
			err(EXIT_FAILURE,"exec failed");
		}
	}


	exit(EXIT_SUCCESS);
}