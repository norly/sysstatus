#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "common.h"


static int linebuf_sane(GlobalData *g)
{
  return (g->linelen < g->linemax);
}


void line_clear(GlobalData *g)
{
  assert(g->linemax > 0);

  g->line[0] = '\0';
  g->linelen = 0;
  g->firstItemDone = 0;

  line_append_str(g, "[");
}


void line_append_strn(GlobalData *g, char *string, size_t len)
{
  assert(linebuf_sane(g));

  if (g->linemax <= g->linelen + len) {
    /* Buffer full. Tough luck. */
    return;
  }

  memcpy(&g->line[g->linelen], string, len);
  g->linelen += len;
  g->line[g->linelen] = '\0';
}


void line_append_str(GlobalData *g, char *string)
{
  line_append_strn(g, string, strlen(string));
}



void line_append_item(GlobalData *g, StatusItem *s)
{
  if (g->firstItemDone) {
    line_append_str(g, ",");
  }
  g->firstItemDone = 1;

  line_append_str(g, "{");

  if (s->color) {
    line_append_str(g, "\"color\":\"");
    line_append_str(g, s->color);
    line_append_str(g, "\",");
  }

  line_append_str(g, "\"full_text\":\"");
  assert(s->text);
  line_append_str(g, s->text);
  line_append_str(g, "\"");

  line_append_str(g, ",\"separator\":false");
  line_append_str(g, ",\"separator_block_width\":14");

  line_append_str(g, "}");
}


void line_print(GlobalData *g)
{
  line_append_str(g, "],");
  puts(g->line);
}


void statusitem_init(StatusItem *s)
{
  s->color = NULL;
  s->text = NULL;
}
