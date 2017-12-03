/*
 * energy.h
 *
 *  Created on: Dec 2, 2017
 *      Author: phlav
 */

#ifndef ENERGY_H_
#define ENERGY_H_

#include "utils.h"

unsigned sumsq(short* data, unsigned n);
unsigned int CalculateFrameEnergy(const tRAW_FRAME* p_vsFrameData);

#endif /* ENERGY_H_ */
