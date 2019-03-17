#ifndef _score_h__
#define _score_h__

#include <util/delay.h>

void updateScore(unsigned char c[3])
{
	if (c[2] == 0x39)
	{
		c[2] = 0x30;
		if (c[1] == 0x39)
		{
			c[1] = 0x30;
			c[0]++;
		}
		else
		{
			c[1]++;
		}
	}
	else
	{
		c[2]++;
	}
}

#endif