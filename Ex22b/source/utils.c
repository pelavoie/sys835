#include "../include/utils.h"
#include "../include/filter.h"

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
void GetFilteredChannelFrame(const tFRAME* f_ptInputFrame, tFRAME* f_ptChFrame, const unsigned int f_ulChannelId)
{
	filterN2((float*)f_ptChFrame, (float*)f_ptInputFrame, b[f_ulChannelId], gains[f_ulChannelId], NUMBER_OF_SAMPLES_PER_FRAME);
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : AppendValueToBuffer
 *
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void AppendChNoiseToBuffer( tBUFFER_1S_NOISE* f_pCircularBuffer, const unsigned int f_ulBufferSize, const float f_lNewData,const unsigned int f_ulChannelId)
{
	static unsigned int ulId[NUMBER_OF_CHANNELS] = {0};
	(*f_pCircularBuffer)[ulId[f_ulChannelId]] = f_lNewData;
	ulId[f_ulChannelId]++;

	if (ulId[f_ulChannelId] > f_ulBufferSize)
	{
		ulId[f_ulChannelId] = 0;
	}
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : CalculateAverage
 *
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
float CalculateAverage(const tBUFFER_1S_NOISE* f_plData, const unsigned int f_ulNumberOfData )
{
	unsigned int ulId = 0;
	float		lsum=0;

	for(ulId = 0; ulId < f_ulNumberOfData; ulId++ )
	{
		lsum += (*f_plData)[ulId];
	}

	return lsum/(float)f_ulNumberOfData;
}

