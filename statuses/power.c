#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "power.h"

void status_power()
{
	char *stline;
	size_t stlen;
	FILE *stfile;

	int batt_now = 0;
	int batt_full = -1;
	int batt_percent = -1;
	int batt_current = 1;
	int batt_voltage = 0;
	float batt_time = -1;
	float batt_watts = -1;

	stfile = fopen("/sys/class/power_supply/BAT0/energy_now", "r");
	if (stfile != NULL)
	{
		stline = NULL;
		stlen = getline(&stline, &stlen, stfile);
		fclose(stfile);

		batt_now = atoi(stline);
		free(stline);
	}

	stfile = fopen("/sys/class/power_supply/BAT0/energy_full", "r");
	if (stfile != NULL)
	{
		stline = NULL;
		stlen = getline(&stline, &stlen, stfile);
		fclose(stfile);

		batt_full = atoi(stline);
		free(stline);
	}

	stfile = fopen("/sys/class/power_supply/BAT0/current_now", "r");
	if (stfile != NULL)
	{
		stline = NULL;
		stlen = getline(&stline, &stlen, stfile);
		fclose(stfile);

		batt_current = atoi(stline);
		free(stline);
	}

	stfile = fopen("/sys/class/power_supply/BAT0/voltage_now", "r");
	if (stfile != NULL)
	{
		stline = NULL;
		stlen = getline(&stline, &stlen, stfile);
		fclose(stfile);

		batt_voltage = atoi(stline);
		free(stline);
	}

    // Hack for chinese battery.
    //batt_now -= 27220000;
    //batt_full = 27000000;

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

	if (batt_watts == 0)	// fully charged and on AC
		printf(" BAT0: %d%% _ _ ", batt_percent);
	else
		printf(" BAT0: %d%% %.1fh %.1fW ", batt_percent, batt_time, batt_watts);

	//fputs(" Power status ", stdout);
}
