/*
 * energy.c
 *
 *  Created on: Dec 2, 2017
 *      Author: phlav
 */
#include "../include/energy.h"
#include <stdint.h>

unsigned int sumsq(float* data, unsigned n)
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

unsigned int CalculateRawFrameEnergy(const tRAW_FRAME* p_vsFrameData)
{
	int i;
	unsigned v2=0;
	for (i = 0; i< NUMBER_OF_SAMPLES_PER_FRAME; i++)
	{
		v2+=((*p_vsFrameData)[i]* (*p_vsFrameData)[i])>>15;
	}
	return v2;
}
double CalculateFrameEnergy(const tFRAME* p_vsFrameData)
{
	int i;
	double v2=0;
	for (i = 0; i< NUMBER_OF_SAMPLES_PER_FRAME; i++)
	{
		//TODO: What if saturation?
		v2 += ((*p_vsFrameData)[i] * (*p_vsFrameData)[i]);
		//v2+=((*p_vsFrameData)[i]* (*p_vsFrameData)[i])>>15;
	}
	return v2;
}

