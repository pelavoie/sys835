
#include "../include/suppression_gain.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : GetSmoothedSuppressionValue
 *
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
float GetSmoothedSuppressionValue(const float f_lCurrentGain, const float f_lPreviousGain)
{
	float lBeta;
	if (f_lCurrentGain >= f_lPreviousGain)
	{
		lBeta = 1;
	}
	else
	{
		lBeta=0.5;
	}
	return f_lPreviousGain + lBeta*(f_lCurrentGain - f_lPreviousGain);
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : ApplyGainOnChFrame
 *
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void ApplyGainOnChFrame(const float f_lGain, tFRAME* f_tFrame )
{
	unsigned int ulSampleId;
	for( ulSampleId = 0; ulSampleId < NUMBER_OF_SAMPLES_PER_FRAME; ulSampleId++ )
	{
		(*f_tFrame)[ulSampleId] = (*f_tFrame)[ulSampleId] * f_lGain;
	}
}
