#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "temp.h"

void status_temp(char *title, char *sysfile)
{
  char stline[16];
  int stfile;
  ssize_t stlen;

  stlen = fileRead(stline, sizeof(stline), sysfile);
  if (stlen <= 0) {
    return;
  }

  /*
   * Read a valid value?
   * Sometimes we get garbage from sysfs...
   */
  if (stlen < 6 || stlen > 7) {
    printf(" ^fg(red)%sERROR ", title);
    return;
  }

  fputs(" ^fg(#FF33FF)", stdout);
  fputs(title, stdout);
  fwrite(stline, 1, stlen - 4, stdout);
  /*
  fputs(".", stdout);
  fwrite(&stline[stlen - 3], 1, 1, stdout);
  */
  fputs("°C ", stdout);
}
