/*
 * energy.c
 *
 *  Created on: Dec 2, 2017
 *      Author: phlav
 */
#include <stdint.h>

unsigned sumsq(float* data, unsigned n)
{
	int i;
	unsigned v2=0;
	for (i = 0; i<n; i++)
	{
		unsigned scaled = (unsigned)(data[i]*UINT8_MAX);
		v2+=(scaled*scaled);
	}
	return v2;
}
