#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

enum {
	Maxline = 1024,
};

int
find_pid(char *pid, char *str)
{
	char *saveptr = NULL;
	char *token;

	token = strtok_r(str, " ", &saveptr);
	if (token == NULL) {
		errx(EXIT_FAILURE, "strtok failed!");
	}

	if (strcmp(token, pid) == 0) {
		return 0;
	}

	while (token != NULL) {
		token = strtok_r(NULL, " ", &saveptr);
		if (token == NULL) {
			break;
		}

		if (strcmp(token, pid) == 0) {
			return 0;
		}
	}

	return 1;

}

void
exec_ps(int *fd)
{
	switch (fork()) {
	case -1:
		err(EXIT_FAILURE, "fork failed!");
	case 0:
		close(fd[0]);
		if (dup2(fd[1], 1) < 0) {
			err(EXIT_FAILURE, "dup failed");
		}
		close(fd[1]);
		execl("/usr/bin/ps", "ps", "aux", NULL);
		err(EXIT_FAILURE, "exec failed");
	}
}

pid_t
read_ps(int *fd, char *arg_pid)
{
	pid_t pid;
	FILE *file;
	char str[Maxline];
	int flag = 1;

	switch (pid = fork()) {
	case -1:
		err(EXIT_FAILURE, "fork failed!");
	case 0:
		close(fd[1]);
		file = fdopen(fd[0], "r");
		if (file == NULL) {
			err(EXIT_FAILURE, "fdopen failed!");
		}

		while (fgets(str, Maxline, file) != NULL) {
			if (find_pid(arg_pid, str) == 0) {
				flag = 0;
				break;
			}

		}

		close(fd[0]);
		fclose(file);

		if (flag == 0) {
			exit(EXIT_SUCCESS);
		} else {
			exit(EXIT_FAILURE);
		}

	}

	return pid;
}

void
usage()
{
	errx(EXIT_FAILURE, "usage: pspid pid");
}

int
main(int argc, char *argv[])
{
	int fd[2];
	pid_t pid;
	int status;

	if (argc != 2) {
		usage();
	}

	if (pipe(fd) < 0) {
		err(EXIT_FAILURE, "cannot make a pipe");
	}

	exec_ps(fd);

	pid = read_ps(fd, argv[1]);

	close(fd[0]);
	close(fd[1]);

	if (waitpid(pid, &status, 0) < 0) {
		err(EXIT_FAILURE, "waitpid failed");
	}

	if (WIFEXITED(status)) {
		exit(WEXITSTATUS(status));
	}

	exit(EXIT_SUCCESS);
}
