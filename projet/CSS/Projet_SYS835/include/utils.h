/*	utils.h
 *
 * List of prototypes for used fonctions
 */
#ifndef __UTILS_H__
#define __UTILS_H__

/************************************* Definitions **********************************************/
#define NUMBER_OF_SAMPLES_PER_FRAME	160
#define NUMBER_OF_CHANNELS			19

#define CONV_FACTOR_FLOAT_TO_SHORT	(float)(1 << 15)

/************************************* Prototypes ***********************************************/
typedef float 		tFRAME[NUMBER_OF_SAMPLES_PER_FRAME];
typedef short		tRAW_FRAME[NUMBER_OF_SAMPLES_PER_FRAME];

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : GetSmoothedSuppressionValue
 *
 * 		arguments:
 * 			- lCurrentGain: The current calculated Gain
 * 			- lPreviousGain : The last applied Gain.
 * 		Description:
 * 			it "smooth" the current calculated gain to minimize brutal variations.
 * 		returns:
 * 			- (float) Smoothed value of suppression to apply.
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
float GetSmoothedSuppressionValue(const float lCurrentGain, const float lPreviousGain);

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : ApplyGainOnChFrame
 *
 * 		arguments:
 * 			- lSuppressionGain: The Gain to apply.
 * 			- vlFrameSamples : Frame containing float data .
 * 		Description:
 * 			Apply gain to the frame data.
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void ApplyGainOnChFrame(const float lSuppressionGain, tFRAME* vlFrameSamples );

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*
 *  function : CombineChFrames
 *
 * 		arguments:
 * 		Description:
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void CombineChFrame(const tFRAME* vChFrame, const unsigned int ulChannelId, tRAW_FRAME* vOutputFrame);

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*
 *  function : ConvertRawFrameToFloatFrame
 *
 * 		arguments:
 * 		Description:
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void ConvertRawFrameToFloatFrame(const tRAW_FRAME* f_ptRawFrame, tFRAME* f_ptFrame);

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*
 *  function : ConvertFrameToRawFrame
 *
 * 		arguments:
 * 		Description:
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void ConvertFrameToRawFrame(const tFRAME* f_ptFrame, tRAW_FRAME* f_ptRawFrame);

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*
 *  function : GetFilteredChannelFrame
 *
 * 		arguments:
 * 		Description:
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void GetFilteredChannelFrame(tFRAME* f_ptInputFrame, tFRAME* f_ptChFrame, const unsigned int f_ulChannelId);

#endif /*__UTILS_H__*/
