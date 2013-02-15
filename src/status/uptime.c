#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "common.h"
#include "tools.h"
#include "config.h"

void status_uptime(GlobalData *g)
{
  StatusItem s;
  char text[16] = { 0 };

  char stline[16];
  ssize_t stlen;
  int i;
  int upts, uptm, upth, uptd;


  statusitem_init(&s);
  s.text = text;

  stlen = fileRead(stline, sizeof(stline), "/proc/uptime");
  if (stlen < 0) {
    s.color = "red";
    s.text = "up: ERROR";
  } else {
    unsigned textlen = 0;

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

    s.color = "#AAAAAA";
    textlen = snprintf(text, sizeof(text), "up: ");
    if (uptd > 0) {
      textlen += snprintf(&text[textlen], sizeof(text) - textlen, "%dd ", uptd);
    }


    snprintf(&text[textlen], sizeof(text) - textlen,
              "%d:%.2d"
              #ifdef SHOW_SECONDS
              ":%.2d"
              #endif

              ""
              ,upth
              ,uptm

              #ifdef SHOW_SECONDS
              ,upts
              #endif
            );

    line_append_item(g, &s);
  }
}
