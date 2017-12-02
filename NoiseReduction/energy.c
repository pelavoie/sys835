/*
 * energy.c
 *
 *  Created on: Dec 2, 2017
 *      Author: phlav
 */


unsigned sumsq(short* data, unsigned n)
{
	int i;
	unsigned v2=0;
	for (i = 0; i<n; i++)
	{
		v2+=(data[i]*data[i])>>15;
	}
	return v2;
}
