#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "battery.h"

#ifndef POWER_BASEDIR
	#define POWER_BASEDIR "/sys/class/power_supply/"
#endif


void status_battery(char *batname)
{
	char batpath[256];
	int batpathlen;

	char stline[16];
	ssize_t stlen;

	int batt_now = 0;
	int batt_full = -1;
	int batt_percent = -1;
	int batt_current = 1;
	int batt_voltage = 0;
	float batt_time = -1;
	float batt_watts = -1;


	// Prepare path
	batpathlen = sizeof(POWER_BASEDIR) - 1 + strlen(batname);
	if (batpathlen + 1 + sizeof("/energy_full") >= sizeof(batpath))
	{
		statusError("status_battery",
			"batpath buffer too small",
			batname);
		return;
	}
	strcpy(batpath, POWER_BASEDIR);
	strcat(batpath, batname);


	// Get info
	strcpy(&batpath[batpathlen], "/energy_now");
	stlen = fileRead(stline, sizeof(stline), batpath);
	if (stlen > 0)
		batt_now = atoi(stline);

	strcpy(&batpath[batpathlen], "/energy_full");
	stlen = fileRead(stline, sizeof(stline), batpath);
	if (stlen > 0)
		batt_full = atoi(stline);

	strcpy(&batpath[batpathlen], "/current_now");
	stlen = fileRead(stline, sizeof(stline), batpath);
	if (stlen > 0)
		batt_current = atoi(stline);

	strcpy(&batpath[batpathlen], "/voltage_now");
	stlen = fileRead(stline, sizeof(stline), batpath);
	if (stlen > 0)
		batt_voltage = atoi(stline);


	// Prettyprint
	if (batt_full > 0)
		batt_percent = batt_now / (batt_full / 100);

	if (batt_percent <= 40) // 40
	{
		if (batt_percent <= 25) // 25
		{
			if (batt_percent <= 10) // 10
				fputs("^fg(red)", stdout);
			else // 11-25%
				fputs("^fg(orange)", stdout);
		}
		else // 26-40%
			fputs("^fg(yellow)", stdout);
	}
	else
	{
		if (batt_percent > 70) // 70
			fputs("^fg(white)", stdout);
		else // 41-70%
			fputs("^fg(green)", stdout);
	}

	batt_time = (float)batt_now / (float)batt_current;
	batt_watts = ((float)batt_voltage / 1000000) * ((float)batt_current / 10000000);

	if (batt_watts == 0)	// fully charged and not in use
		printf(" %s: %d%% _ _ ", batname, batt_percent);
	else
		printf(" %s: %d%% %.1fh %.1fW ",
			batname, batt_percent, batt_time, batt_watts);
}
