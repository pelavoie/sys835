/*
 * 	main_func.h
 *
 *  Created on: Dec 2, 2017
 *      Author: Eric Lacerte and Philippe Lavoie
 *
 *  File containing all different main functions (real-time, test)
 *
 */
#ifndef __MAIN_FUNC_H__
#define __MAIN_FUNC_H__

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
 *  function : MainRt
 * 		Description:
 * 			Real Time implementation of NoiseSuppressionAlgorithm
 * 			it Uses Interruptions for burst
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void MainRt();

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
 *  function : MainTest
 * 		Description:
 * 			Test implementation of NoiseSuppressionAlgorithm
 * 			it Uses a Binary test files to produce Frames data.
 * 		returns:
 * 			- void
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void MainTest();


#endif /*__MAIN_FUNC_H__*/
