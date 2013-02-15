#include <stdio.h>
#include <time.h>

#include "common.h"
#include "config.h"


void status_datetime(GlobalData *g)
{
  StatusItem s;
  char text[32] = { 0 };

  time_t nows = 0;
  struct tm *nowtm;


  statusitem_init(&s);
  s.text = text;

  nows = time(NULL);
  if (nows == ((time_t) -1)) {
    s.color = "red";
    s.text = "ERROR: DATETIME";

    line_append_item(g, &s);
  } else {
    nowtm = localtime(&nows);

    s.color = "#666666";
    snprintf(text, sizeof(text),
              "%d.%d.%d",
              nowtm->tm_mday,
              (nowtm->tm_mon) + 1,
              (nowtm->tm_year) + 1900
            );
    line_append_item(g, &s);

    s.color = "grey";
    snprintf(text, sizeof(text),
              "%d:%.2d"
              #ifdef SHOW_SECONDS
              ":%.2d"
              #endif
              ,nowtm->tm_hour,
              nowtm->tm_min

              #ifdef SHOW_SECONDS
              ,nowtm -> tm_sec
              #endif
            );
    line_append_item(g, &s);
  }
}
