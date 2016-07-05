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

  long long memtotal = 0;
  long long memfree = 0;
  long long memused;
  long long membuffers = 0;
  long long memcached = 0;


  statusitem_init(&s);
  s.text = text;

  stfile = fopen("/proc/meminfo", "r");
  if (stfile != NULL) {
    stlen = getline(&stline, &stlen, stfile);
    memtotal = atoll(&stline[16]);

    stlen = getline(&stline, &stlen, stfile);
    memfree = atoll(&stline[16]);

    stlen = getline(&stline, &stlen, stfile);
    if (stlen > 13 && !memcmp(stline, "MemAvailable:", 13)) {
      stlen = getline(&stline, &stlen, stfile);
    }
    membuffers = atoll(&stline[16]);

    stlen = getline(&stline, &stlen, stfile);
    memcached = atoll(&stline[16]);
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

    snprintf(text, sizeof(text), "Mem: %lld M", memused);

    line_append_item(g, &s);
  }
}
