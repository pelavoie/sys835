/*
 * noisedetector.c
 *
 *  Created on: Nov 29, 2017
 *      Author: phlav
 */


static unsigned energybin[128] = {0};
static unsigned cumulative[128] = {0};
static unsigned threshold = 1024;

unsigned noisedetector(unsigned energy)
{
	int i;
	unsigned candidate;
	float decay;
	// decay
	for (i=0; i<128; i++)
	{
		energybin[i] = energybin[i]*0.995;
	}
	i = energy/256;
	if (i>127)
		i=127;
	energybin[i] = energybin[i] + 160;
	// create cumulative histogram
	cumulative[0] = energybin[0];
	for (i=1; i<128; i++)
	{
		cumulative[i] = cumulative[i-1] + energybin[i];
	}
	// noise absent?
	if (cumulative[9] >= cumulative[127]/4)
	{
		candidate = 0;
	}
	else
	{
		// if noise present, find threshold candidate
		unsigned eightypct = 0.8*cumulative[127];
		for (i=9; i<128; i++)
		{
			if ((cumulative[i]>=eightypct) && (cumulative[i-1]<eightypct))
			{
				candidate = i * 256; // energy quantum
			}
			if (candidate>=threshold)
			{
				decay = 0.95;
			}
			else
			{
				decay = 0.60653;
			}
		}
	}
	threshold = candidate + decay * (threshold - candidate);
	if (threshold < 1024)
	{
		threshold = 1024;
	}
	return threshold;

}
