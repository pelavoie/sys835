/*
 * main.c
 */
#include <stdio.h>
#include <math.h>
#include "include/utils.h"
#include "include/suppression_curves.h"

#define EPSILON 	INDEX_EPSILON_4

extern const float 	BesselFiltersTables[NUMBER_OF_EPSILON][NUMBER_OF_GAIN_VALUE];
const float* 		vlSuppresionGainTable = BesselFiltersTables[EPSILON];

void main(void) {

	tFRAME			vlInputFrameSamples;

	unsigned int	ulChannelId;
	tFRAME			vlChFrameSamples[NUMBER_OF_CHANNELS];
	float 			lChEnergy;
	float			lChNoise;
	float			lChLastNoise[NUMBER_OF_CHANNELS];

	float 			lChParameter;
	unsigned int 	ulChSuppressionId;
	float			lChSuppressionGain;
	float			lChPreviousSuppressionGain[NUMBER_OF_CHANNELS] = {0};

	tFRAME			vlOutputFrameSamples;

	// interrupts burst of 160 samples...
	unsigned int ulSampleId;
	for( ulSampleId = 0; ulSampleId < NUMBER_OF_SAMPLES_PER_FRAME; ulSampleId++)
	{
		vlInputFrameSamples[ulSampleId] = 0.3;
	}

	for( ulChannelId=0; ulChannelId < NUMBER_OF_CHANNELS; ulChannelId++ )
	{
		lChEnergy = 0.6;
		lChNoise = 0.5;
		lChLastNoise[ulChannelId] = 0.2;

		// Calculate Channel Gain Parameter
		lChParameter = (lChEnergy - lChLastNoise[ulChannelId] )/lChEnergy;

		// Determine the Gain from lookup table.
		ulChSuppressionId = floor((float)NUMBER_OF_GAIN_VALUE * lChParameter);
		lChSuppressionGain = vlSuppresionGainTable[ulChSuppressionId];

		//Smooth the Gain
		lChSuppressionGain = GetSmoothedSuppressionValue(lChSuppressionGain, lChPreviousSuppressionGain[ulChannelId]  );

		//Apply Gain
		ApplyGainOnChFrame(lChSuppressionGain, &vlChFrameSamples[ulChannelId]);

		// Save Previous Values
		lChPreviousSuppressionGain[ulChannelId]  	= lChSuppressionGain;
		lChLastNoise[ulChannelId] 					= lChNoise;
	}

	// Combine Channels Frames
	CombineChFrames( &vlChFrameSamples, &vlOutputFrameSamples );
}
