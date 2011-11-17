#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
//#include <ctype.h>
//#include <memory.h>
//#include <stdint.h>
//#include <sys/socket.h>
//#include <sys/un.h>
#include "statuses/uptime.h"
#include "statuses/memusage.h"
#include "statuses/cpuusage.h"
#include "statuses/netif.h"
#include "statuses/netif_named.h"
#include "statuses/power.h"
#include "statuses/volume_alsa.h"
#include "statuses/temp.h"
#include "statuses/datetime.h"
#include "config.h"

void updatestatus()
{
	//status_uptime();

	status_cpuusage();

	status_power();

	status_memusage();

	//status_netif();
	status_netif_named("eth0");
	status_netif_named("eth1");
	status_netif_named("wlan0");
	status_netif_named("wlan1");
	status_netif_named("ppp0");

	status_temp("GPU: ", "/sys/class/hwmon/hwmon0/device/temp4_input");
	status_temp("CPU: ", "/sys/class/hwmon/hwmon0/device/temp2_input");

	status_volume_alsa("default", "Master", 0);

	status_datetime();

	fputs("\n", stdout);
	fflush(stdout);
}

int main()
{
	struct timeval tv;

	updatestatus();

	for(;;)
	{
		tv.tv_sec = UPDATE_SECS;
		tv.tv_usec = 0;

		select(0, NULL, NULL, NULL, &tv);

		updatestatus();
	}

	return 0;
}
