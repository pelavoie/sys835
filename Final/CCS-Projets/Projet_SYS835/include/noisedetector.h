/*
 * noisedetector.h
 *
 *  Created on: Dec 2, 2017
 *      Author: phlav
 */

#ifndef NOISEDETECTOR_H_
#define NOISEDETECTOR_H_

/*  function : noisedetector
 *
 * 		arguments:
 * 			- energy: 		the current frame's energy.
 *
 * 		Description:
 * 			une implementation de l'algorithme de detection du niveau d'energie du bruit de
 * 			Robert J. McAulay and Marilyn L. Malpass, (1980)
 * 			SPEECH ENHANCEMENT USING A SOFT-DECISION NOISE SUPPRESSION FILTER
 *
 * 		returns:
 * 			- the current noise threshold.
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

unsigned noisedetector(unsigned energy);


#endif /* NOISEDETECTOR_H_ */
