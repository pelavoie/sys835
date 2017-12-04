
#include <math.h>
#include <stdint.h>
#include "../include/algorithm.h"
#include "../include/suppression_gain.h"
#include "../include/energy.h"
#include "../include/noisedetector.h"

#define ALPHA					(float)0.1
#define NUMBER_FRAME_IN_1_SEC	50


void NoiseSuppressionAlgorithm(const tRAW_FRAME* f_ptRawInputFrame, tRAW_FRAME* f_ptRawOutputFrame)
{
	tFRAME			vlInputFrameData= {0.0};


	unsigned int	ulFrameEnergy;
	unsigned int	ulNoiseThreshold;
	unsigned int	bFrameIsNoise;

	unsigned int	ulChannelId;
	double 			lChEnergy;

	float					lChNoise;
	float					lChNoiseAvg;
	static float			lChLastNoise[NUMBER_OF_CHANNELS] = {0.0};
	static tBUFFER_1S_NOISE	lChLastNoise1Sec[NUMBER_OF_CHANNELS];

	float 			lChParameter;
	const double 	vlSuppresionTable[NUMBER_OF_SUPPRESSION_VALUES] = SUPPRESSION_FILTER_EPS_2;
	unsigned int 	ulChSuppressionId;
	float			lChSuppressionGain;
	static float	lChPreviousSuppressionGain[NUMBER_OF_CHANNELS]= {0.0};


	//Convert Frame Data to Float
	ConvertRawFrameToFloatFrame(f_ptRawInputFrame, &vlInputFrameData);

	// Calculate Frame Energy
	ulFrameEnergy = CalculateFrameEnergyScaled((const tFRAME *)&vlInputFrameData);

	//Noise Detector
	ulNoiseThreshold = UINT16_MAX;//noisedetector(ulFrameEnergy);
	bFrameIsNoise = ulFrameEnergy < ulNoiseThreshold;

	for( ulChannelId=0; ulChannelId < NUMBER_OF_CHANNELS; ulChannelId++ )
	{
		tFRAME			vlChFrameSamples = {0.0};

		//Separate in Channel Frames
		GetFilteredChannelFrame((const tFRAME *)&vlInputFrameData, &vlChFrameSamples, ulChannelId);

		//Calculate Channel Energy
		lChEnergy = CalculateFrameEnergy((const tFRAME *) &vlChFrameSamples);

		//Compute Channel Noise Level
		if( bFrameIsNoise )
		{
			AppendChNoiseToBuffer( &lChLastNoise1Sec[ulChannelId], NUMBER_FRAME_IN_1_SEC, lChEnergy, ulChannelId);
			lChNoiseAvg = CalculateAverage( (const tBUFFER_1S_NOISE *)&lChLastNoise1Sec[ulChannelId], NUMBER_FRAME_IN_1_SEC);
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
		if( lChParameter >= 1.0)
		{
			lChParameter = 1.0;
		}
		if(lChParameter <= 0.0)
		{
			lChParameter = 0.0;
		}
		//TODO: Rounding by typecast unsigned int... OK?
		ulChSuppressionId = (unsigned int)((float)NUMBER_OF_SUPPRESSION_VALUES * lChParameter - 1);
		lChSuppressionGain = vlSuppresionTable[ulChSuppressionId];

		//Smooth the Gain
		lChSuppressionGain = GetSmoothedSuppressionValue(lChSuppressionGain, lChPreviousSuppressionGain[ulChannelId]  );

		//Apply Gain
		ApplyGainOnChFrame(lChSuppressionGain, &vlChFrameSamples);

		// Combine Channels Frames
		CombineChFrame( (const tFRAME *)&vlChFrameSamples, ulChannelId, f_ptRawOutputFrame);

		// Save Previous Values
		lChPreviousSuppressionGain[ulChannelId]  	= lChSuppressionGain;
		lChLastNoise[ulChannelId] 					= lChNoise;
	}
	return;
}
