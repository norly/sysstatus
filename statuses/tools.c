#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "tools.h"

char powerToChar(int power)
{
	switch(power)
	{
		case 0:
			return 'b';
		case 1:
			return 'k';
		case 2:
			return 'M';
		case 3:
			return 'G';
		case 4:
			return 'T';
		case 5:
			return 'P';
		case 6:
			return 'E';
	}

	return '?';
}


void statusError(char *where, char *what, char *extra)
{
	fprintf(stderr, "%s: %s", where, what);
	if (extra)
		fprintf(stderr, " -- %s", extra);
	fputs("\n", stderr);
}


ssize_t fileRead(char *buf, size_t bufsize, char *file)
{
	int fd;
	int readbytes;

	fd = open(file, 0);
	if (fd < 0)
		return -1;

	readbytes = read(fd, buf, bufsize - 1);
	close(fd);

	if (readbytes > 0)
		buf[readbytes] = '\0';
	else
		buf[0] = '\0';

	return readbytes;
}
