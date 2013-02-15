
#ifndef __TOOLS_H__
#define __TOOLS_H__

char powerToChar(int power);
void statusError(char *where, char *what, char *extra);
ssize_t fileRead(char *buf, size_t bufsize, char *file);

#endif
