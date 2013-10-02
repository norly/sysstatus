#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "common.h"
#include "tools.h"


void status_temp(GlobalData *g, char *title, char *sysfile)
{
  StatusItem s;
  char text[16] = { 0 };

  char stline[16];
  ssize_t stlen;


  statusitem_init(&s);
  s.text = text;

  stlen = fileRead(stline, sizeof(stline), sysfile);
  if (stlen <= 0) {
    return;
  }

  /*
   * Read a valid value?
   * Sometimes we get garbage from sysfs...
   */
  if (stlen < 6 || stlen > 7) {
    s.color = "#FF0000";  // red
    snprintf(text, sizeof(text), "%sERROR", title);
  } else {
    stline[stlen - 4] = '\0';

    s.color = "#FF33FF";
    snprintf(text, sizeof(text), "%s%s C", title, stline);
  }

  line_append_item(g, &s);
}
