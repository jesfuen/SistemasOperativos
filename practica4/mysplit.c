#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include <limits.h>


void
usage()
{
	errx(EXIT_FAILURE,"usage: myslpit N file");
}

int
to_int(char *s)
{
	long number;
	char *endptr = NULL;

	number = strtol(s,&endptr,10);
	if (number <= 0 || *endptr != '\0' || number > INT_MAX) {
		usage();
	}

	return (int)number;
}

void
split_file(int fdin, int n, char *buf, char *name)
{
	int nr;
	int len;
	int nfich = 0;
	char *filename;
	int fdout;


	while ((nr = read(fdin,buf,(size_t)n)) != 0)
	{
		if (nr < 0) {
			free(buf);
			close(fdin);
			err(EXIT_FAILURE,"read");
		}

		len = snprintf(NULL,0,"%03d%s",nfich,name) + 1;
		filename = malloc(len * sizeof(char));
		if (filename == NULL) {
			free(buf);
			err(EXIT_FAILURE,"malloc");
		}

		len = snprintf(filename,(size_t)len,"%03d%s",nfich,name);
		if (len < 0) {
			free(filename);
			free(buf);
			errx(EXIT_FAILURE,"snprintf failed!!");
		}

		fdout = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (fdout < 0) {
			free(buf);
			free(filename);
			err(EXIT_FAILURE,"open");
		}

		if (write(fdout,buf,(size_t)nr) != nr) {
			free(filename);
			free(buf);
			err(EXIT_FAILURE,"write");
		}

		close(fdout);

		nfich++;
		free(filename);
	}
}

int
main(int argc, char *argv[])
{
	int fdin;
	int n;
	char *buf;

	if (argc != 3) {
		usage();
	}

	n = to_int(argv[1]);
	fdin = open(argv[2], O_RDONLY);
	if (fdin < 0) {
		err(EXIT_FAILURE,"can't open file");
	}

	buf = malloc(n * sizeof(char));
	if (buf == NULL) {
		err(EXIT_FAILURE,"malloc");
	}

	split_file(fdin,n,buf,argv[2]);

	close(fdin);

	free(buf);
	exit(EXIT_SUCCESS);

}