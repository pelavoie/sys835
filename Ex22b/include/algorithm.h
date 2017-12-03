/*	algorithm.h
 *
 * Contains Algorithm for Digital Processing Algorithms
 *
 */

#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "utils.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : NoiseSuppressionAlgorithm
 *
 * 		arguments:
 * 			- p_vlInputFrameData: 	A frame of float Input Data.
 * 			- p_vlOutputFrameData:	A frame of float to write Output Data.

 * 		Description:
 * 			implementation of A REAL-TIME NOISE SUPPRESSION FILTER FOR SPEECH ENHANCEMENT AND ROBUST CHANNEL VOCODING
 * 			algortihm from Robert J. McAulay and Marilyn L. Malpass, (1980)
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void NoiseSuppressionAlgorithm(const  tRAW_FRAME* p_vlInputFrameData, tRAW_FRAME* p_vlOutputFrameData);
#endif /*__ALGORITHM_H__*/