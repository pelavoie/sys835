
#include <math.h>
#include "../include/algorithm.h"
#include "../include/suppression_gain.h"
#include "../include/energy.h"
#include "../include/noisedetector.h"

#define ALPHA					(float)0.4
#define NUMBER_FRAME_IN_1_SEC	50

void NoiseSuppressionAlgorithm(const tRAW_FRAME* p_vlInputRawFrameData, tRAW_FRAME* p_vlOutputFrameData)
{
	tFRAME			vlInputFrameData= {0.0};
	tFRAME			vlChFrameSamples = {0.0};

	unsigned int	ulFrameEnergy;
	unsigned int	ulNoiseThreshold;
	unsigned int	bFrameIsNoise;

	unsigned int	ulChannelId;
	double 			lChEnergy;

	float			lChNoise;
	float			lChNoiseAvg;
	static float	lChLastNoise[NUMBER_OF_CHANNELS] = {0.0};
	static float	lChLastNoise1Sec[NUMBER_OF_CHANNELS][NUMBER_FRAME_IN_1_SEC] = {0.0};

	float 			lChParameter;
	const double 	vlSuppresionTable[NUMBER_OF_SUPPRESSION_VALUES] = SUPPRESSION_FILTER_EPS_2;
	unsigned int 	ulChSuppressionId;
	float			lChSuppressionGain;
	static float	lChPreviousSuppressionGain[NUMBER_OF_CHANNELS]= {0.0};

	// Calculate Frame Energy
	ulFrameEnergy = CalculateRawFrameEnergy(p_vlInputRawFrameData);

	//Noise Detector
	ulNoiseThreshold = noisedetector(ulFrameEnergy);
	bFrameIsNoise = ulFrameEnergy < ulNoiseThreshold;

	//Convert Frame Data to Float
	ConvertRawFrameToFloatFrame(p_vlInputRawFrameData, &vlInputFrameData);

	for( ulChannelId=0; ulChannelId < NUMBER_OF_CHANNELS; ulChannelId++ )
	{
		//Separate in Channel Frames
		GetFilteredChannelFrame((const tFRAME *)&vlInputFrameData, &vlChFrameSamples, ulChannelId);

		//Calculate Channel Energy
		lChEnergy = CalculateFrameEnergy((const tFRAME *) &vlChFrameSamples);
		//TODO : Overflow?
		/*if(lChEnergy >= FLT_MAX || lChParameter <= -FLT_MAX)
		{
			lChEnergy = 1.0;
		}*/

		//Compute Channel Noise Level
		if( bFrameIsNoise )
		{
			AppendValueToBuffer( lChLastNoise1Sec[ulChannelId], NUMBER_FRAME_IN_1_SEC, lChEnergy);
			lChNoiseAvg = CalculateAverage( lChLastNoise1Sec[ulChannelId], NUMBER_FRAME_IN_1_SEC);
			lChNoise = lChLastNoise[ulChannelId] + ALPHA*(lChNoiseAvg - lChLastNoise[ulChannelId]);
		}
		else
		{
			lChNoise = lChLastNoise[ulChannelId] + ALPHA*(lChEnergy - lChLastNoise[ulChannelId]);
		}

		// Calculate Channel Gain Parameter
		lChParameter = (lChEnergy - lChNoise )/lChEnergy;

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
