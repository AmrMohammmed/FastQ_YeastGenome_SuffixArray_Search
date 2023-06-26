#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "string.h"


int main()
{
	for (int c = 1; c < 17; c++) {
		char integer_string[32];
		sprintf(integer_string, "%d",c);
		if (c < 10) {
			integer_string[1] = integer_string[0];
			integer_string[0] = '0';
			integer_string[2] = '\0';
		}
		char other_string[64] = "chr";

		strcat(other_string, integer_string);
		strcat(other_string, ".fsa");
		printf("%s\n", other_string);
	
		int fd, n, pos;
		char *r;
		fd = open(other_string, O_RDONLY);

		pos = lseek(fd, 0, SEEK_END);

		r = (char*)malloc(pos * sizeof(char));

		lseek(fd, 0, SEEK_SET);

		n = read(fd, r, pos);
		FILE *fptr = fopen("genome3.fsa", "a");

		for (int i = 0; i <pos; i++) {

			if (r[i] == '\n'|| r[i] == '10')
				continue;
			fprintf(fptr, "%c", r[i]);

		}
		free(r);
		close(fd);
	}
	
	int fd, n, pos;
	char *r;
	fd = open("chrmt.fsa", O_RDONLY);

	pos = lseek(fd, 0, SEEK_END);

	r = (char*)malloc(pos * sizeof(char));

	lseek(fd, 0, SEEK_SET);

	n = read(fd, r, pos);
	FILE *fptr = fopen("genome3.fsa", "a");

	for (int i = 0; i < pos; i++) {


		if (r[i] == '\n'||r[i] == '10')
			continue;
		fprintf(fptr, "%c", r[i]);

	}
	free(r);
	close(fd);

	return 0;
}