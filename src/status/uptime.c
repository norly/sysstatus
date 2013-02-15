#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "status/uptime.h"
#include "tools.h"
#include "config.h"

void status_uptime()
{
  char stline[16];
  ssize_t stlen;
  int i;
  int upts, uptm, upth, uptd;

  fputs(" ^fg(#AAAAAA)up: ", stdout);

  stlen = fileRead(stline, sizeof(stline), "/proc/uptime");
  if (stlen < 0) {
    fputs(" ^fg(red)ERROR ", stdout);
    return;
  }

  /* Cut first element */
  for(i = 0; i < stlen; i++) {
    if (stline[i] == ' ') {
      stline[i] = '\0';
      break;
    }
  }

  // Split time into days, hours, mins, secs
  upts = atoi(stline);
  uptd = upts / (24 * 60 * 60);
  upts -= uptd * (24 * 60 * 60);
  upth = upts / (60 * 60);
  upts -= upth * (60 * 60);
  uptm = upts / (60);
  upts -= uptm * (60);

  if (uptd > 0) {
    printf("%dd ", uptd);
  }

  printf("%d:%.2d"
          #ifdef SHOW_SECONDS
          ":%.2d"
          #endif

          " "
          ,upth
          ,uptm

          #ifdef SHOW_SECONDS
          ,upts
          #endif
        );
}
