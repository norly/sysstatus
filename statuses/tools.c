#include "tools.h"

char powertochar(int power)
{
	switch(power)
	{
		case 0:
			return 'b';
		case 1:
			return 'k';
		case 2:
			return 'M';
		case 3:
			return 'G';
		case 4:
			return 'T';
		case 5:
			return 'P';
		case 6:
			return 'E';
	}
	
	return '?';
}
