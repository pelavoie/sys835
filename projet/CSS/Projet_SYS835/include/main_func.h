/*	main_func.h
 *
 * Contains different main functions (real-time, test)
 *
 */

#ifndef __MAIN_FUNC_H__
#define __MAIN_FUNC_H__

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : MainRt
 * 		Description:
 * 			Real Time implementation of NoiseSuppressionAlgorithm
 * 			it Uses Interruptions for burst
 * 		returns:
 * 			- int (ErrorCode)
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
int MainRt();

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : MainTest
 * 		Description:
 * 			Test implementation of NoiseSuppressionAlgorithm
 * 			it Uses a Binary test files to produce Frames data.
 * 		returns:
 * 			- int (ErrorCode)
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
int MainTest();


#endif /*__MAIN_FUNC_H__*/
