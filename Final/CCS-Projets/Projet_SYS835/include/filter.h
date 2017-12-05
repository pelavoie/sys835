/*
 * filter.h
 *
 *  Created on: Dec 2, 2017
 *      Author: phlav
 */

#ifndef FILTER_H_
#define FILTER_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : filterN2
 *
 * 		arguments:
 * 			- out: 		A pointer to an array of float for output data.
 * 			- in: 		A pointer to an array of float with input data.
 * 			- coeffs: 	A pointer to an array of float containing 4 coefficients.
 * 			- gain: 	The initial gain to apply to input.
 * 			- nb: 		The number of inputs to process.
 *
 * 		Description:
 * 			A bandpass Butterworth order 2 filter.
 *
 * 		returns:
 * 			- void.
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void filterN2(float* out, float* in, float* coeffs, float gain, unsigned nb);
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*  function : FilterASM
 *
 * 		arguments:
 * 			- out: 		A pointer to an array of float for output data.
 * 			- in: 		A pointer to an array of float with input data.
 * 			- coeffs: 	A pointer to an array of float containing 4 coefficients.
 * 			- gain: 	The initial gain to apply to input.
 * 			- nb: 		The number of inputs to process.
 *
 * 		Description:
 * 			A bandpass Butterworth order 2 filter.
 *
 * 		returns:
 * 			- void.
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void FilterASM(float* out, float* in, float* coeffs, float gain, unsigned nb);

float b[17][4] = {
	{ -0.914976, 3.738840, -5.732650, 3.908784},
	{ -0.894874, 3.656101, -5.626426, 3.865056},
	{ -0.894874, 3.610879, -5.534543, 3.817249},
	{ -0.894874, 3.543395, -5.399553, 3.745908},
	{ -0.884990, 3.425661, -5.196307, 3.641665},
	{ -0.875215, 3.264477, -4.914571, 3.489704},
	{ -0.855987, 3.037219, -4.543366, 3.283173},
	{ -0.846532, 2.791558, -4.139478, 3.034506},
	{ -0.837182, 2.477683, -3.659877, 2.708398},
	{ -0.809746, 2.074027, -3.121837, 2.305518},
	{ -0.791958, 1.596935, -2.575772, 1.795189},
	{ -0.766007, 1.013978, -2.072003, 1.159238},
	{ -0.732726, 0.373255, -1.738872, 0.436466},
	{ -0.700897, -0.361250, -1.694456, -0.432120},
	{ -0.655742, -1.119944, -2.067502, -1.386389},
	{ -0.606759, -1.795081, -2.862854, -2.313941},
	{ -0.543166, -2.269324, -3.851631, -3.102773},
};
float gains[17] = {
	 1.058546241e+003,
	 6.847831502e+002,
	 6.847831502e+002,
	 6.847831502e+002,
	 5.689655658e+002,
	 4.806381793e+002,
	 3.568756175e+002,
	 3.125167033e+002,
	 2.761148367e+002,
	 1.988801298e+002,
	 1.644858571e+002,
	 1.278738361e+002,
	 9.585509742e+001,
	 7.485478157e+001,
	 5.464828250e+001,
	 4.027725681e+001,
	 2.821863531e+001,
};



#endif /* FILTER_H_ */
