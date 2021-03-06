#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "common.h"
#include "config.h"

#ifndef NUM_CPUS
  #define NUM_CPUS 1
#endif
#ifndef CPU_HISTORY_SIZE
  #define CPU_HISTORY_SIZE 1
#endif
#if CPU_HISTORY_SIZE < 1
  #define CPU_HISTORY_SIZE 1
#endif


unsigned long last_cpu_used = 0;
unsigned long last_cpu_total = 0;
float cpu_history[CPU_HISTORY_SIZE]; // don't care about init values

void status_cpuusage(GlobalData *g)
{
  StatusItem s;
  char text[32] = { 0 };

  double loadavg[3] = { -13.37, -13.37, -13.37 } ;

  char *stline = NULL;
  size_t stlen;
  FILE *stfile;

  unsigned long cpu_user;
  unsigned long cpu_nice;
  unsigned long cpu_sys;
  unsigned long cpu_used;
  unsigned long cpu_idle;
  unsigned long cpu_total;
  int i;


  statusitem_init(&s);
  s.text = text;

  // Error signaling color
  s.color = "#FFFF00";  // yellow

  stfile = fopen("/proc/stat", "r");
  if (stfile != NULL) {
    for(i = CPU_HISTORY_SIZE - 1; i > 0; i--) {
      cpu_history[i] = cpu_history[i - 1];
    }

    stlen = getline(&stline, &stlen, stfile);
    fclose(stfile);

    if ( 4 == sscanf(stline, "%*s %ld %ld %ld %ld",
                    &cpu_user, &cpu_nice, &cpu_sys, &cpu_idle) ) {
      cpu_used = cpu_user + cpu_nice + cpu_sys;
      cpu_total = cpu_used + cpu_idle;

      // Now do the percentage
      cpu_history[0] = (float)(cpu_used - last_cpu_used) /
                        (float)(cpu_total - last_cpu_total);

      last_cpu_used = cpu_used;
      last_cpu_total = cpu_total;


      if (cpu_history[0] < 0.4) {
        // CPU idling OK
        s.color = "#0077FF";
      } else {
        // CPU busy
        s.color = "#FF00FF";
      }
    }

    free(stline);
  }


  if (getloadavg(loadavg, 3) > 0) {
    snprintf(text, sizeof(text),
              "%s%.0f,%.0f,%.0f,%.0f",
              cpu_history[0] < 0.1000 ? " " : "",
              cpu_history[0] * 100,
              loadavg[0] * (100 / 1),
              loadavg[1] * (100 / 1),  // (100 / NUM_CPUS)
              loadavg[2] * (100 / 1));
  }

  line_append_item(g, &s);
}
