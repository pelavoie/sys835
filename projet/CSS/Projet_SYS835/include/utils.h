/*	utils.h
 *
 * List of prototypes for used fonctions
 */
#ifndef __UTILS_H__
#define __UTILS_H__

/************************************* Definitions **********************************************/
#define NUMBER_OF_SAMPLES_PER_FRAME	160
#define NUMBER_OF_CHANNELS			19

/************************************* Prototypes ***********************************************/
typedef float 	tFRAME[NUMBER_OF_SAMPLES_PER_FRAME];
typedef tFRAME 	tCHANNELS_FRAMES[NUMBER_OF_CHANNELS];

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
void CombineChFrames(tCHANNELS_FRAMES* vChFrames, tFRAME* vOutputFrames);

#endif /*__UTILS_H__*/
