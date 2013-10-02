#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "tools.h"

#ifndef POWER_BASEDIR
  #define POWER_BASEDIR "/sys/class/power_supply/"
#endif


void status_battery(GlobalData *g, char *batname)
{
  StatusItem s;
  char text[32] = { 0 };

  char batpath[256];
  int batpathlen;

  char stline[16];
  ssize_t stlen;

  int chargeNow = 0;
  int chargeFull = -1;
  int chargePercent = -1;
  int battW = 1;
  float battTime = -1;


  statusitem_init(&s);
  s.text = text;

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


  /* Prettyprint */
  if (chargeFull > 0) {
    chargePercent = chargeNow / (chargeFull / 100);
  }

  if (chargePercent <= 40) {
    if (chargePercent <= 25) {
      if (chargePercent <= 10) {
        s.color = "#FF0000";  // red
      } else {
        // 11-25%
        s.color = "#FFA500";  // orange
      }
    } else {
      // 26-40%
      s.color = "#FFFF00";  // yellow
    }
  } else {
    if (chargePercent > 70) {
      s.color = "#FFFFFF";  // white
    } else {
      // 41-70%
      s.color = "#22FF22";  // green
    }
  }

  battTime = (float)chargeNow / (float)battW;

  if (battW == 0) {
    // fully charged and not in use
    snprintf(text, sizeof(text), "%s: %d%% _ _",
              batname, chargePercent);
  } else {
    snprintf(text, sizeof(text), "%s: %d%% %.1fh %.1fW",
              batname, chargePercent, battTime, (float)battW / 1000000.0);
  }

  line_append_item(g, &s);
}
