/*	utils.h
 *
 * List of prototypes for used fonctions
 */
#ifndef __UTILS_H__
#define __UTILS_H__

/************************************* Definitions **********************************************/
#define NUMBER_OF_CHANNELS				17
#define NUMBER_OF_SAMPLES_PER_FRAME		160
#define CONV_FACTOR_FLOAT_TO_SHORT		(float)(1 << 15)

typedef float 		tFRAME[NUMBER_OF_SAMPLES_PER_FRAME];
typedef short		tRAW_FRAME[NUMBER_OF_SAMPLES_PER_FRAME];
typedef float		tBUFFER_1S_NOISE[50];

/************************************* Prototypes ***********************************************/
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
 *  function : CombineChFrames
 *
 * 		arguments:
 * 			f_ptChFrame : 		A pointer to a Channel Frame of data as float
 * 			f_ulChannelId :		The Channel Id
 * 			f_ptOutputFrame:	A pointer to a Frame were the results should be written.
 * 		Description:
 * 			Combine the input channel frame to the output frame with a 180° phase.
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void CombineChFrame(const tFRAME* f_ptChFrame, const unsigned int f_ulChannelId, tRAW_FRAME* f_ptOutputFrame);

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
 *  function : ConvertRawFrameToFloatFrame
 *
 * 		arguments:
 * 			f_ptRawFrame : 		A pointer to an input Channel Frame Data as short
 * 			f_ptFrame :			A pointer to an output Frame Data as float
 * 		Description:
 * 			Combine the input channel frame to the output frame with a 180° phase.
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void ConvertRawFrameToFloatFrame(const tRAW_FRAME* f_ptRawFrame, tFRAME* f_ptFrame);

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*
 *  function : GetFilteredChannelFrame
 *
 * 		arguments:
 * 			f_ptInputFrame : 	A pointer to an input Frame Data as float
 * 			f_ptChFrame :		A pointer to an output Channel Frame Data as float
 * 			f_ulChannelId:		The Channel Id
 * 		Description:
 * 			Apply the Channel corresponding Butterworth filter to the input frame.
 * 			The output is place in f_ptChFrame and represents the Channel Frame data.
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void GetFilteredChannelFrame(const tFRAME* f_ptInputFrame, tFRAME* f_ptChFrame, const unsigned int f_ulChannelId);

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*
 *  function : AppendChNoiseToBuffer
 *
 * 		arguments:
 * 			f_ptChNoiseBuffer : A pointer to the Channel Noise 1 second Buffer.
 * 			f_ulBufferSize	:	The size of the f_ptChNoiseBuffer.
 * 			f_lNewData		:	The new noise value to append.
 * 			f_ulChannelId	: 	The Channel Id
 *
 * 		Description:
 * 			Append the new value of noise to a circular buffer for the Channel.
 * 			This implements a 1 second buffer of noise value to each channels.
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void AppendChNoiseToBuffer( tBUFFER_1S_NOISE* f_ptChNoiseBuffer, const unsigned int f_ulBufferSize, const float f_lNewData,const unsigned int f_ulChannelId);

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*
 *  function : CalculateAverage
 *
 * 		arguments:
 * 			f_ptChNoiseBuffer : A pointer to the Channel Noise 1 second Buffer.
 * 			f_ulBufferSize	:	The size of the f_ptChNoiseBuffer.
 * 		Description:
 * 			Calculate the Average of the Channel Noise buffer of 1 seconds.
 * 			It is used to smooths the value noise.
 * 		returns:
 * 			- float, the average noise value of the Channel Noise buffer of 1 seconds.
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
float CalculateAverage(const tBUFFER_1S_NOISE* f_ptChNoiseBuffer, const unsigned int f_ulBufferSize );

#endif /*__UTILS_H__*/
