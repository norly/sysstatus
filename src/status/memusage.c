#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "tools.h"


void status_memusage(GlobalData *g)
{
  StatusItem s;
  char text[16] = { 0 };

  char *stline = NULL;
  size_t stlen;
  FILE *stfile;

  int memtotal = 0;
  int memfree = 0;
  int memused;
  int membuffers = 0;
  int memcached = 0;


  statusitem_init(&s);
  s.text = text;

  stfile = fopen("/proc/meminfo", "r");
  if (stfile != NULL) {
    stlen = getline(&stline, &stlen, stfile);
    memtotal = atoi(&stline[17]);

    stlen = getline(&stline, &stlen, stfile);
    memfree = atoi(&stline[17]);

    stlen = getline(&stline, &stlen, stfile);
    if (stlen > 13 && !memcmp(stline, "MemAvailable:", 13)) {
      stlen = getline(&stline, &stlen, stfile);
    }
    membuffers = atoi(&stline[17]);

    stlen = getline(&stline, &stlen, stfile);
    memcached = atoi(&stline[17]);
    free(stline);

    fclose(stfile);

    memused = memtotal - memfree - memcached - membuffers;

    memused /= 1024;	// Just show MBs used

    /* Change color based on % of RAM used */
    if ((float)memused / (float)memtotal < 0.85) {
      s.color = "#22FF22";  // green
    } else {
      s.color = "#FF0000";  // red
    }

    snprintf(text, sizeof(text), "Mem: %d M", memused);

    line_append_item(g, &s);
  }
}
