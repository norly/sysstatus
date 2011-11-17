#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "temp.h"

void status_temp(char *title, char *sysfile)
{
	char stline[16];
	int stfile;
	size_t stlen;

	stfile = open(sysfile, 0);
	if (stfile != -1)
	{
		stlen = read(stfile, stline, sizeof(stline));
		close(stfile);
		if (stlen >= 6 && stlen <= 7)
		{
			fputs(" ^fg(#FF33FF)", stdout);
			fputs(title, stdout);
			fwrite(stline, 1, stlen - 4, stdout);
			/*
			fputs(".", stdout);
			fwrite(&stline[stlen - 3], 1, 1, stdout);
			*/
			fputs("°C ", stdout);
		}
		else
			printf(" ^fg(red)%sERROR ", title);
	}
}
