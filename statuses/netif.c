#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "netif.h"
#include "tools.h"
#include "../config.h"

#ifndef NETIF_BASEDIR
	#define NETIF_BASEDIR "/sys/class/net/"
#endif


void status_netif(char *ifname)
{
	char ifpath[256];
	int ifpathlen;

	char stline[16];
	ssize_t stlen;

	double ifsum = 0.0;
	int ifsumpower;


	// Prepare path
	ifpathlen = sizeof(NETIF_BASEDIR) - 1 + strlen(ifname);
	if (ifpathlen + 1 + sizeof("/statistics/rx_bytes") >= sizeof(ifpath))
	{
		statusError("status_netif",
			"ifpath buffer too small",
			ifname);
		return;
	}
	strcpy(ifpath, NETIF_BASEDIR);
	strcat(ifpath, ifname);


	// Is the interface up?
	if (access(ifpath, F_OK))
	{
		//printf(" ^fg(grey)[%s] ", ifname);
		return;
	}


	strcpy(&ifpath[ifpathlen], "/carrier");
	stlen = fileRead(stline, sizeof(stline), ifpath);
	if (stlen > 0)
	{
		if (stline[0] == '1')
		{
			fputs("^fg(yellow)", stdout);
		}
		else
		{
			//fputs("^fg(red)", stdout);
			return;
		}
	}

	strcpy(&ifpath[ifpathlen], "/statistics/rx_bytes");
	stlen = fileRead(stline, sizeof(stline), ifpath);
	if (stlen > 0)
		ifsum = atof(stline);

	strcpy(&ifpath[ifpathlen], "/statistics/tx_bytes");
	stlen = fileRead(stline, sizeof(stline), ifpath);
	if (stlen > 0)
		ifsum += atof(stline);


	for(ifsumpower = 0; ifsum >= 1024.0; ifsumpower++)
		ifsum = ifsum / 1024;

	printf(" %s: %.*f %c ", ifname,
				ifsumpower ? ifsumpower - 1 : ifsumpower,
				ifsum,
				powerToChar(ifsumpower));
}
