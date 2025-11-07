#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>

struct Killprocs
{
	pid_t process;
	char *killed;
};


void
usage(void)
{
	errx(EXIT_FAILURE,"usage: ./killprocs pid [pid ...]");
}

int
to_int(char *s)
{
	long number;
	char *endptr = NULL;

	number = strtol(s,&endptr,10);

	if (number < 0 || number > INT_MAX || *endptr != '\0') {
		return 0;
	}

	return 1;
}

pid_t
execute_kill(char *s)
{
	pid_t pid;


	
	pid = fork();
	switch (pid)
	{
	case -1:
		err(EXIT_FAILURE,"fork failed!");
	case 0:
		execl("/bin/kill", "kill", "-9", s, NULL);
		err(EXIT_FAILURE,"execl failed!");
	default:
		return pid;
	}
}

pid_t
wait_kills()
{
	int sts;
	pid_t pid;

	pid = wait(&sts);

	if (pid == -1) {
		err(EXIT_FAILURE,"wait failed!");
	}

	if (WIFEXITED(sts)) {
		if (WEXITSTATUS(sts) != 0) {
			return pid;
		}
	}

	return 1;


}

int
main(int argc, char *argv[])
{
	int i;
	int pid;
	int flag = 1;

	if (argc == 1) {
		usage();
	}

	argc--;
	argv++;

	struct Killprocs *ptr = (struct Killprocs *)malloc(argc * sizeof(struct Killprocs));

	if (ptr == NULL) {
		err(EXIT_FAILURE,"malloc failed.");
	}

	
	for (i = 0; i < argc; i++)
	{
		if (!to_int(argv[i])) 
		{
			usage();
			free(ptr);
		}

		ptr[i].process = execute_kill(argv[i]);
		ptr[i].killed = argv[i];
	}


	for (i = 0; i < argc; i++)
	{
		pid = wait_kills();
		if ((pid == ptr[i].process)) {
			fprintf(stderr,"ERROR: can't kill PID %s\n",ptr[i].killed);
			flag = 0;
		}
	}
	
	

	if (!flag) {
		free(ptr);
		exit(EXIT_FAILURE);
	}

	free(ptr);

	exit(EXIT_SUCCESS);
}