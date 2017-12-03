
#include <math.h>
#include "../include/algorithm.h"
#include "../include/suppression_gain.h"
#include "../include/energy.h"
#include "../include/noisedetector.h"

#define ALPHA	(float)0.4

void NoiseSuppressionAlgorithm(const tRAW_FRAME* p_vlInputRawFrameData, tRAW_FRAME* p_vlOutputFrameData)
{
	unsigned int	ulFrameEnergy;
	unsigned int	ulNoiseThreshold;
	unsigned int	bFrameIsNoise;

	const double 	vlSuppresionTable[NUMBER_OF_SUPPRESSION_VALUES] = SUPPRESSION_FILTER_EPS_2;

	unsigned int	ulChannelId;
	double 			lChEnergy;
	float			lChNoise;
	float			lChLastNoise[NUMBER_OF_CHANNELS] = {0};

	float 			lChParameter;
	unsigned int 	ulChSuppressionId;
	float			lChSuppressionGain;
	float			lChPreviousSuppressionGain[NUMBER_OF_CHANNELS]= {1.0};

	tFRAME			vlInputFrameData;
	tFRAME			vlChFrameSamples;

	// Calculate Frame Energy
	ulFrameEnergy = CalculateRawFrameEnergy(p_vlInputRawFrameData);

	//Noise Detector
	ulNoiseThreshold = noisedetector(ulFrameEnergy);
	bFrameIsNoise = ulFrameEnergy < ulNoiseThreshold;

	//TODO : What type of Input Data (Float or Short)?
	ConvertRawFrameToFloatFrame(p_vlInputRawFrameData, &vlInputFrameData);

	for( ulChannelId=0; ulChannelId < NUMBER_OF_CHANNELS; ulChannelId++ )
	{
		//Separate in Channel Frames
		GetFilteredChannelFrame((const tFRAME *)&vlInputFrameData, &vlChFrameSamples, ulChannelId);

		//Calculate Channel Energy
		//TODO : Overflow?
		lChEnergy = CalculateFrameEnergy((const tFRAME *) &vlChFrameSamples);

		//Compute Channel Noise Level
		if( bFrameIsNoise )
		{
			//TODO: 1 sec buffer smoothing to Compute Channel Noise Level

		}
		else
		{
			lChNoise = lChLastNoise[ulChannelId] + ALPHA*(lChEnergy - lChLastNoise[ulChannelId]);
		}

		// Calculate Channel Gain Parameter
		lChParameter = (lChEnergy - lChLastNoise[ulChannelId] )/lChEnergy;

		// Determine the Gain from lookup table.
		//Overflow
		if(lChParameter >= FLT_MAX || lChParameter <= -FLT_MAX)
		{
			lChParameter = 1.0;
		}
		//TODO: Rounding by typecast unsigned int... OK?
		ulChSuppressionId = (unsigned int)((float)NUMBER_OF_SUPPRESSION_VALUES * lChParameter - 1);
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
