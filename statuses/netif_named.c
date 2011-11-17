#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "netif_named.h"
#include "tools.h"

#define NETIF_BASEDIR "/sys/class/net/"

void status_netif_named(char *ifname)
{
	char stline[16];
	int stfile;
	size_t stlen;
	
	double ifsum;
	int ifsumpower;
	
	char *stfilename = NULL;
	
	stfilename = malloc(sizeof(NETIF_BASEDIR) - 1 + strlen(ifname) + sizeof("/statistics/rx_bytes"));
	
	strcpy(stfilename, NETIF_BASEDIR);
	strcat(stfilename, ifname);
	
	if (access(stfilename, F_OK))
	{
		//printf(" ^fg(grey)[%s] ", ifname);
		return;
	}
	
	strcat(stfilename, "/carrier");
	stfile = open(stfilename, 0);
	if (stfile != -1)
	{
		stlen = read(stfile, stline, sizeof(stline) - 1);
		close(stfile);
		if (stline[0] == '1')
			fputs("^fg(yellow)", stdout);
		else
		{
			//fputs("^fg(red)", stdout);
			return;
		}
	}
	
	strcpy(stfilename, NETIF_BASEDIR);
	strcat(stfilename, ifname);
	strcat(stfilename, "/statistics/rx_bytes");
	stfile = open(stfilename, 0);
	if (stfile != -1)
	{
		stlen = read(stfile, stline, sizeof(stline) - 1);
		close(stfile);
		stline[stlen] = '\0';
		ifsum = atof(stline);
	}

	strcpy(stfilename, NETIF_BASEDIR);
	strcat(stfilename, ifname);
	strcat(stfilename, "/statistics/tx_bytes");
	stfile = open(stfilename, 0);
	if (stfile != -1)
	{
		stlen = read(stfile, stline, sizeof(stline) - 1);
		close(stfile);
		stline[stlen] = '\0';
		ifsum += atof(stline);
	}
	
	for(ifsumpower = 0; ifsum >= 1024.0; ifsumpower++)
		ifsum = ifsum / 1024;
	
	printf(" %s: %.*f %c ", ifname, ifsumpower ? ifsumpower - 1 : ifsumpower, ifsum, powertochar(ifsumpower));
}
