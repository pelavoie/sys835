/*
 * 	main_func.h
 *
 *  Created on: Dec 2, 2017
 *      Author: Eric Lacerte and Philippe Lavoie
 *
 *  File containing all energy calculations
 *
 */

#ifndef ENERGY_H_
#define ENERGY_H_

#include "utils.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : CalculateFrameEnergy
 *
 * 		arguments:
 * 			- f_ptFrame: 		A pointer to a Frame of data as float.
 *
 * 		Description:
 * 			Calculate the Frame Energy using (Eq.1)
 *
 * 		returns:
 * 			- double, the Frame Energy.
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
double 	CalculateFrameEnergy(const tFRAME* f_ptFrame);

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : CalculateFrameEnergyScaled
 *
 * 		arguments:
 * 			- f_ptFrame: 		A pointer to a Frame of data as float.
 *
 * 		Description:
 * 			Calculate the Frame Energy using (Eq.1) and scaling for each samples (UINT8_MAX)
 *
 * 		returns:
 * 			- Unsigned int, the scaled Frame Energy.
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
unsigned int CalculateFrameEnergyScaled(const tFRAME* f_ptFrame);

#endif /* ENERGY_H_ */
