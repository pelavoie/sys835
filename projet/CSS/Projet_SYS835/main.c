/*
 * main.c
 */
#include <stdio.h>
//#include <math.h>
#include "include/utils.h"
#include "include/suppression_curves.h"

#define EPSILON 	INDEX_EPSILON_4

extern const float 	BesselFiltersTables[NUMBER_OF_EPSILON][NUMBER_OF_SUPPRESSION_VALUES];
const float* 		vlSuppresionGainTable = BesselFiltersTables[EPSILON];

unsigned int	ulChannelId;
float 			lChEnergy;
float			lChNoise;
float			lChLastNoise[NUMBER_OF_CHANNELS];

float 			lChParameter;
unsigned int 	ulChSuppressionId;
float			lChSuppressionGain;
float			lChPreviousSuppressionGain[NUMBER_OF_CHANNELS];

tFRAME			vlInputFrameSamples;
tFRAME			vlChFrameSamples;
tFRAME			vlOutputFrameSamples;

void main(void) {



	//TODO: interrupts burst of 160 samples...
	unsigned int ulSampleId;
	for( ulSampleId = 0; ulSampleId < NUMBER_OF_SAMPLES_PER_FRAME; ulSampleId++)
	{
		vlChFrameSamples[ulSampleId] = 0.3f;
	}
	//TODO Noise Detector

	//TODO Separate in Channel Frames

	for( ulChannelId=0; ulChannelId < NUMBER_OF_CHANNELS; ulChannelId++ )
	{
		//TODO Compute Channel Energy
		lChEnergy = 0.6f;

		//TODO Compute Channel Noise Level
		lChNoise = 0.5f;

		lChLastNoise[ulChannelId] = 0.2f;
		lChPreviousSuppressionGain[ulChannelId] = 0;

		// Calculate Channel Gain Parameter
		lChParameter = (lChEnergy - lChLastNoise[ulChannelId] )/lChEnergy;

		// Determine the Gain from lookup table.
		ulChSuppressionId = (unsigned int)((float)NUMBER_OF_SUPPRESSION_VALUES * lChParameter);
		lChSuppressionGain = vlSuppresionGainTable[ulChSuppressionId];

		//Smooth the Gain
		lChSuppressionGain = GetSmoothedSuppressionValue(lChSuppressionGain, lChPreviousSuppressionGain[ulChannelId]  );

		//Apply Gain
		ApplyGainOnChFrame(lChSuppressionGain, &vlChFrameSamples);

		// Combine Channels Frames
		CombineChFrame( &vlChFrameSamples, &vlOutputFrameSamples, ulChannelId);

		// Save Previous Values
		lChPreviousSuppressionGain[ulChannelId]  	= lChSuppressionGain;
		lChLastNoise[ulChannelId] 					= lChNoise;
	}

	lChEnergy = 0.6f;
	return;


}
