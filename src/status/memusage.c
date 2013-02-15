#include <stdio.h>
#include <stdlib.h>

#include "status/memusage.h"
#include "tools.h"


void status_memusage()
{
  char *stline = NULL;
  size_t stlen;
  FILE *stfile;

  int memtotal = 0;
  int memfree = 0;
  int memused;
  int membuffers = 0;
  int memcached = 0;


  stfile = fopen("/proc/meminfo", "r");
  if (stfile != NULL) {
    stlen = getline(&stline, &stlen, stfile);
    memtotal = atoi(&stline[17]);

    stlen = getline(&stline, &stlen, stfile);
    memfree = atoi(&stline[17]);

    stlen = getline(&stline, &stlen, stfile);
    membuffers = atoi(&stline[17]);

    stlen = getline(&stline, &stlen, stfile);
    memcached = atoi(&stline[17]);
    free(stline);

    fclose(stfile);

    memused = memtotal - memfree - memcached - membuffers;

    memused /= 1024;	// Just show MBs used

    /* Change color based on % of RAM used */
    if ((float)memused / (float)memtotal < 0.85) {
      fputs("^fg(green)", stdout);
    } else {
      fputs("^fg(red)", stdout);
    }

    printf(" Mem: %d M ", memused);
  }
}
