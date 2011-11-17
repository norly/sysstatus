#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "netif.h"
#include "tools.h"
#include "../config.h"

void status_netif()
{
	char stline[16];
	int stfile;
	size_t stlen;
	
	double ifsum;
	int ifsumpower;
	
	
	stfile = open("/sys/class/net/" IFNAME "/carrier", 0);
	if (stfile != -1)
	{
		stlen = read(stfile, stline, sizeof(stline) - 1);
		close(stfile);
		if (stline[0] == '1')
			fputs("^fg(yellow)", stdout);
		else
			fputs("^fg(red)", stdout);
	}
	
	stfile = open("/sys/class/net/" IFNAME "/statistics/rx_bytes", 0);
	if (stfile != -1)
	{
		stlen = read(stfile, stline, sizeof(stline) - 1);
		close(stfile);
		stline[stlen] = '\0';
		ifsum = atof(stline);
	}

	stfile = open("/sys/class/net/" IFNAME "/statistics/tx_bytes", 0);
	if (stfile != -1)
	{
		stlen = read(stfile, stline, sizeof(stline) - 1);
		close(stfile);
		stline[stlen] = '\0';
		ifsum += atof(stline);
	}
	
	for(ifsumpower = 0; ifsum >= 1024.0; ifsumpower++)
		ifsum = ifsum / 1024;
	
	printf(" %s: %.*f %c ", IFNAME, ifsumpower ? ifsumpower - 1 : ifsumpower, ifsum, powertochar(ifsumpower));
}
