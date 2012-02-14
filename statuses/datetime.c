#include <stdio.h>
#include <time.h>
#include "datetime.h"
#include "../config.h"

void status_datetime()
{
	time_t nows = 0;
	struct tm *nowtm;

	nows = time(NULL);
	if (nows == ((time_t) -1))
	{
		printf(" ^fg(red)ERROR: DATETIME");
		return;
	}

	nowtm = localtime(&nows);

	printf(" ^fg(#666666)%d.%d.%d  ^fg(grey)%d:%.2d"

		#ifdef SHOW_SECONDS
		":%.2d"
		#endif
		" "
		,nowtm -> tm_mday,
		(nowtm -> tm_mon) + 1,
		(nowtm -> tm_year) + 1900,
		nowtm -> tm_hour,
		nowtm -> tm_min

		#ifdef SHOW_SECONDS
		,nowtm -> tm_sec
		#endif

		);
}
