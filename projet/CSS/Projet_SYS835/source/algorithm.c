
#include <math.h>
#include "../include/algorithm.h"
#include "../include/suppression_gain.h"
#include "../include/energy.h"
#include "../include/noisedetector.h"

void NoiseSuppressionAlgorithm(const tRAW_FRAME* p_vlInputRawFrameData, tRAW_FRAME* p_vlOutputFrameData)
{
	unsigned int	ulFrameEnergy;
	unsigned int	ulNoiseThreshold;
	unsigned int	bFrameIsNoise;

	const double 	vlSuppresionTable[NUMBER_OF_SUPPRESSION_VALUES] = SUPPRESSION_FILTER_EPS_2;

	unsigned int	ulChannelId;
	float 			lChEnergy;
	float			lChNoise;
	float			lChLastNoise[NUMBER_OF_CHANNELS] = {0};

	float 			lChParameter;
	unsigned int 	ulChSuppressionId;
	float			lChSuppressionGain;
	float			lChPreviousSuppressionGain[NUMBER_OF_CHANNELS]= {0};

	tFRAME			vlInputFrameData;
	tFRAME			vlChFrameSamples;

	// Calculate Frame Energy
	ulFrameEnergy = CalculateFrameEnergy(p_vlInputRawFrameData);

	//Noise Detector
	ulNoiseThreshold = noisedetector(ulFrameEnergy);
	bFrameIsNoise = ulFrameEnergy < ulNoiseThreshold;

	//TODO : What type of Input Data (Float or Short)?
	ConvertRawFrameToFloatFrame(p_vlInputRawFrameData, &vlInputFrameData);

	for( ulChannelId=0; ulChannelId < NUMBER_OF_CHANNELS; ulChannelId++ )
	{
		//Separate in Channel Frames
		GetFilteredChannelFrame((const tFRAME *)&vlInputFrameData, &vlChFrameSamples, ulChannelId);

		//TODO Compute Channel Energy
		lChEnergy = 0.2;

		//TODO Compute Channel Noise Level
		lChNoise = 0.5f;
		if( bFrameIsNoise )
		{

		}
		else
		{

		}

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
		CombineChFrame( (const tFRAME *)&vlChFrameSamples, ulChannelId, p_vlOutputFrameData);

		// Save Previous Values
		lChPreviousSuppressionGain[ulChannelId]  	= lChSuppressionGain;
		lChLastNoise[ulChannelId] 					= lChNoise;
	}
	return;
}
