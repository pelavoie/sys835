#include "../include/utils.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : GetSmoothedSuppressionValue
 *
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
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
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : ApplyGainOnChFrame
 *
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void ApplyGainOnChFrame(const float lSuppressionGain, tFRAME* vlFrameSamples )
{
	unsigned int ulSampleId;
	for( ulSampleId = 0; ulSampleId < NUMBER_OF_SAMPLES_PER_FRAME; ulSampleId++ )
	{
		(*vlFrameSamples)[ulSampleId] = (*vlFrameSamples)[ulSampleId] * lSuppressionGain;
	}
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : CombineChFrames
 *
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void CombineChFrame(tFRAME* vChFrame, tFRAME* vOutputFrame, const unsigned int ulChannelId)
{
	unsigned int ulDataId;

	if(ulChannelId % 2)
	{
		for(ulDataId = 0; ulDataId < NUMBER_OF_SAMPLES_PER_FRAME; ulDataId ++)
		{
			(*vOutputFrame)[ulDataId] += (*vChFrame)[ulDataId];
		}
	}
	else
	{
		for(ulDataId = 0; ulDataId < NUMBER_OF_SAMPLES_PER_FRAME; ulDataId ++)
		{
			(*vOutputFrame)[ulDataId] -= (*vChFrame)[ulDataId];
		}
	}
}
