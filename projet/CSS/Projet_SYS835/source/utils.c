#include "../include/utils.h"
#include "../include/filter.h"

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
void CombineChFrame(const tFRAME* vChFrame, const unsigned int ulChannelId, tRAW_FRAME* vOutputFrame)
{
	unsigned int ulDataId;

	for(ulDataId = 0; ulDataId < NUMBER_OF_SAMPLES_PER_FRAME; ulDataId ++)
	{
		if(ulChannelId % 2)
		{
			(*vOutputFrame)[ulDataId] += (short)((*vChFrame)[ulDataId]*CONV_FACTOR_FLOAT_TO_SHORT);
		}
		else
		{
			(*vOutputFrame)[ulDataId] -= (short)((*vChFrame)[ulDataId]*CONV_FACTOR_FLOAT_TO_SHORT);
		}
	}
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : ConvertRawFrameToFloatFrame
 *
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void ConvertRawFrameToFloatFrame(const tRAW_FRAME* f_ptRawFrame, tFRAME* f_ptFrame)
{
	unsigned int i = 0;
	for (i=0; i<160; i++)
	{
		(*f_ptFrame)[i] = (float)((*f_ptRawFrame)[i]/CONV_FACTOR_FLOAT_TO_SHORT);
	}
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : ConvertRawFrameToFloatFrame
 *
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void ConvertFrameToRawFrame(const tFRAME* f_ptFrame ,tRAW_FRAME* f_ptRawFrame)
{
	unsigned int i = 0;
	for (i=0; i<160; i++)
	{
		(*f_ptRawFrame)[i] = (float)((*f_ptFrame)[i]*CONV_FACTOR_FLOAT_TO_SHORT);
	}
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : GetFilteredChannelFrame
 *
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void GetFilteredChannelFrame(tFRAME* f_ptInputFrame, tFRAME* f_ptChFrame, const unsigned int f_ulChannelId)
{
	filterN2((float*)f_ptChFrame, (float*)f_ptInputFrame, b[f_ulChannelId], gains[f_ulChannelId], NUMBER_OF_SAMPLES_PER_FRAME);
}
