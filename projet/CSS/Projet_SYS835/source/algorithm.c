
#include <math.h>
#include "../include/algorithm.h"
#include "../include/suppression_curves.h"

void NoiseSuppressionAlgorithm( tFRAME* p_vlInputFrameData, tFRAME* p_vlOutputFrameData)
{
	const double 	vlSuppresionTable[NUMBER_OF_SUPPRESSION_VALUES] = SUPPRESSION_FILTER_EPS_2;

	unsigned int	ulChannelId;
	float 			lChEnergy;
	float			lChNoise;
	float			lChLastNoise[NUMBER_OF_CHANNELS];

	float 			lChParameter;
	unsigned int 	ulChSuppressionId;
	float			lChSuppressionGain;
	float			lChPreviousSuppressionGain[NUMBER_OF_CHANNELS];

	tFRAME			vlChFrameSamples;

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
		lChSuppressionGain = vlSuppresionTable[ulChSuppressionId];

		//Smooth the Gain
		lChSuppressionGain = GetSmoothedSuppressionValue(lChSuppressionGain, lChPreviousSuppressionGain[ulChannelId]  );

		//Apply Gain
		ApplyGainOnChFrame(lChSuppressionGain, &vlChFrameSamples);

		// Combine Channels Frames
		CombineChFrame( &vlChFrameSamples, p_vlOutputFrameData, ulChannelId);

		// Save Previous Values
		lChPreviousSuppressionGain[ulChannelId]  	= lChSuppressionGain;
		lChLastNoise[ulChannelId] 					= lChNoise;
	}
	return;
}
