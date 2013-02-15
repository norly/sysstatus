#ifndef __COMMON_H__
#define __COMMON_H__

#include <sys/types.h>

typedef struct GlobalData GlobalData;

typedef struct {
  char *color;
  char *text;
} StatusItem;


typedef struct GlobalData {
  char *line;
  size_t linelen;
  size_t linemax; /* Buffer size, including NUL */
} GlobalData;



void line_clear(GlobalData *g);
void line_append_strn(GlobalData *g, char *string, size_t len);
void line_append_str(GlobalData *g, char *string);

void line_append_item(GlobalData *g, StatusItem *s);

void line_print(GlobalData *g);

void statusitem_init(StatusItem *s);

#endif
