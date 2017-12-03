/*
 * energy.c
 *
 *  Created on: Dec 2, 2017
 *      Author: phlav
 */
#include "../include/energy.h"

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

unsigned int CalculateFrameEnergy(tRAW_FRAME* p_vsFrameData)
{
	int i;
	unsigned v2=0;
	for (i = 0; i< NUMBER_OF_SAMPLES_PER_FRAME; i++)
	{
		v2+=((*p_vsFrameData)[i]* (*p_vsFrameData)[i])>>15;
	}
	return v2;
}
