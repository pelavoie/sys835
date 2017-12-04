/*
 * 	main_func.h
 *
 *  Created on: Dec 2, 2017
 *      Author: Eric Lacerte and Philippe Lavoie
 *
 *  File containing algorithm for Digital Processing
 *
 */

#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "utils.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : NoiseSuppressionAlgorithm
 *
 * 		arguments:
 * 			- f_ptRawInputFrame: 	A pointer to a frame of Input Data as short.
 * 			- f_ptRawOutputFrame:	A pointer to a frame to write Output Data as short.

 * 		Description:
 * 			implementation of A REAL-TIME NOISE SUPPRESSION FILTER FOR SPEECH ENHANCEMENT AND ROBUST CHANNEL VOCODING
 * 			algorithm from Robert J. McAulay and Marilyn L. Malpass, (1980)
 *
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void NoiseSuppressionAlgorithm(const  tRAW_FRAME* f_ptRawInputFrame, tRAW_FRAME* f_ptRawOutputFrame);

#endif /*__ALGORITHM_H__*/
