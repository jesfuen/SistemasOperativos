#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <err.h>
#include <sys/stat.h>

void
usage()
{
	errx(EXIT_FAILURE,"usage: /path/to/myls");
}

int ls() {

	DIR *d;
	struct dirent *ent;
	struct stat st;
	int flag = 0;
	char *type;

	d = opendir(".");
	if (d == NULL) {
		err(EXIT_FAILURE,"opendir failed");
	}

	while ((ent = readdir(d)) != NULL) {
		if (lstat(ent->d_name,&st) == -1) {
			warn("lstat failed for %s", ent->d_name);
			flag = 1;
			continue;
		}
		if (S_ISDIR(st.st_mode)) {
			type = "d";
		} else if (S_ISREG(st.st_mode)) {
			type = "f";
		} else if (S_ISLNK(st.st_mode)) {
			type = "l";
		} else {
			type = "o";
		}

		printf("%s\t%d\t%d\t%ld\t%s\n",type,st.st_uid,st.st_gid,st.st_size,ent->d_name);
	}
	closedir(d);

	return flag;
}

int
main(int argc, char *argv[])
{

	int flag;

	if (argc != 1) {
		usage();
	}

	flag = ls();

	if (flag != 0) {
		err(EXIT_FAILURE,"lstat failed!");
	}

	exit(EXIT_SUCCESS);
}