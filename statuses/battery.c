#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

  int chargeNow = 0;
  int chargeFull = -1;
  int chargePercent = -1;
  int battW = 1;
  int battV = 0;
  float battTime = -1;


  /* Prepare path */
  batpathlen = sizeof(POWER_BASEDIR) - 1 + strlen(batname);
  if (batpathlen + 1 + sizeof("/energy_full") >= sizeof(batpath)) {
    statusError("status_battery",
                "batpath buffer too small",
                batname);
    return;
  }
  strcpy(batpath, POWER_BASEDIR);
  strcat(batpath, batname);


  /* Is the battery present? */
  if (access(batpath, F_OK)) {
    //printf(" ^fg(grey)[%s] ", batname);
    return;
  }


  /* Get info */
  strcpy(&batpath[batpathlen], "/energy_now");
  stlen = fileRead(stline, sizeof(stline), batpath);
  if (stlen > 0) {
    chargeNow = atoi(stline);
  }

  strcpy(&batpath[batpathlen], "/energy_full");
  stlen = fileRead(stline, sizeof(stline), batpath);
  if (stlen > 0) {
    chargeFull = atoi(stline);
  }

  strcpy(&batpath[batpathlen], "/power_now");
  stlen = fileRead(stline, sizeof(stline), batpath);
  if (stlen > 0) {
    battW = atoi(stline);
  }

  strcpy(&batpath[batpathlen], "/voltage_now");
  stlen = fileRead(stline, sizeof(stline), batpath);
  if (stlen > 0) {
    battV = atoi(stline);
  }


  /* Prettyprint */
  if (chargeFull > 0) {
    chargePercent = chargeNow / (chargeFull / 100);
  }

  if (chargePercent <= 40) {
    if (chargePercent <= 25) {
      if (chargePercent <= 10) {
        fputs("^fg(red)", stdout);
      } else {
        // 11-25%
        fputs("^fg(orange)", stdout);
      }
    } else {
      // 26-40%
      fputs("^fg(yellow)", stdout);
    }
  } else {
    if (chargePercent > 70) {
      fputs("^fg(white)", stdout);
    } else {
      // 41-70%
      fputs("^fg(green)", stdout);
    }
  }

  battTime = (float)chargeNow / (float)battW;

  if (battW == 0) {
    // fully charged and not in use
    printf(" %s: %d%% _ _ ",
            batname, chargePercent);
  } else {
    printf(" %s: %d%% %.1fh %.1fW ",
            batname, chargePercent, battTime, (float)battW / 1000000.0);
  }
}
