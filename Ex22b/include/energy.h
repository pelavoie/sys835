/*
 * energy.h
 *
 *  Created on: Dec 2, 2017
 *      Author: phlav
 */

#ifndef ENERGY_H_
#define ENERGY_H_

#include "utils.h"

unsigned int CalculateRawFrameEnergy(const tRAW_FRAME* p_vsFrameData);
double CalculateFrameEnergy(const tFRAME* p_vsFrameData);

unsigned sumsq(float* data, unsigned n);


#endif /* ENERGY_H_ */
