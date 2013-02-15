#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "status/fan.h"
#include "tools.h"


void status_fan(char *title, char *sysfile)
{
  char stline[16];
  ssize_t stlen;

  stlen = fileRead(stline, sizeof(stline), sysfile);
  if (stlen <= 0) {
    return;
  }

  // Read a valid value? Sometimes we get garbage from sysfs...
  if (stlen > 5) {
    printf(" ^fg(red)%sERROR ", title);
    return;
  }

  fputs(" ^fg(#CCCCCC)", stdout);
  fputs(title, stdout);
  fwrite(stline, 1, stlen - 1, stdout);
  fputs(" rpm ", stdout);
}
