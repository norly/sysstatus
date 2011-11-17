#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "uptime.h"

void status_uptime()
{
	char stline[16];
	int stfile;
	size_t stlen;
	int i;
	int upts, uptm, upth, uptd;
	
	stfile = open("/proc/uptime", 0);
	if (stfile != -1)
	{
		stlen = read(stfile, stline, sizeof(stline));
		close(stfile);
		
		for(i = 0; i < stlen; i++)
			if (stline[i] == ' ')
				stline[i] = '\0';
		
		upts = atoi(stline);
		uptd = upts / (24 * 60 * 60);
		upts -= uptd * (24 * 60 * 60);
		upth = upts / (60 * 60);
		upts -= upth * (60 * 60);
		uptm = upts / (60);
		upts -= uptm * (60);
		
		fputs(" ^fg(#AAAAAA)up: ", stdout);
		
		if (uptd > 0)
			printf("%dd ", uptd);
		
		printf("%d:%.2d"
			
			#ifdef SHOW_SECONDS
			":%.2d"
			#endif
			
			" "
			,upth
			,uptm
			
			#ifdef SHOW_SECONDS
			,upts
			#endif
			);
	}
}
