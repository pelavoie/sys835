#include "../include/utils.h"

float GetSmoothedSuppressionValue(const float lCurrentGain, const float lPreviousGain)
{
	float lBeta;
	if (lCurrentGain >= lPreviousGain)
	{
		lBeta = 1;
	}
	else
	{
		lBeta=0.5;
	}
	return lPreviousGain + lBeta*(lCurrentGain - lPreviousGain);
}

void ApplyGainOnChFrame(const float lSuppressionGain, tFRAME* vlFrameSamples )
{
	unsigned int ulSampleId;
	for( ulSampleId = 0; ulSampleId < NUMBER_OF_SAMPLES_PER_FRAME; ulSampleId++ )
	{
		*vlFrameSamples[ulSampleId] = *vlFrameSamples[ulSampleId] * lSuppressionGain;
	}
}

void CombineChFrames(tCHANNELS_FRAMES* vChFrames, tFRAME* vOutputFrames)
{
	unsigned int ulChannelId;
	unsigned int ulDataId;
	for( ulChannelId = 0; ulChannelId < NUMBER_OF_CHANNELS; ulChannelId++ )
	{
		if(ulChannelId % 2)
		{
			for(ulDataId = 0; ulDataId < NUMBER_OF_SAMPLES_PER_FRAME; ulDataId ++)
			{
				*vOutputFrames[ulDataId] += *vChFrames[ulChannelId][ulDataId];
			}
		}
		else
		{
			for(ulDataId = 0; ulDataId < NUMBER_OF_SAMPLES_PER_FRAME; ulDataId ++)
			{
				*vOutputFrames[ulDataId] -= *vChFrames[ulChannelId][ulDataId];
			}
		}
	}
}
