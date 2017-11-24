/*
 * filter.c
 *
 *  Created on: Nov 17, 2017
 *      Author: phlav
 */


/* Digital filter designed by mkfilter/mkshape/gencode   A.J. Fisher
   Command line: /www/usr/fisher/helpers/mkfilter -Bu -Bp -o 2 -a 1.2500000000e-02 2.5000000000e-02 -l */

#define NZEROS 4
#define NPOLES 4
#define GAIN   6.845238328e+02

static float xv[NZEROS+1], yv[NPOLES+1];

void filterN2(float* out, float* in, float* a, float* b, unsigned nb)
  { int i;
	for (i=0;i<nb;i++)
      { xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4];
        xv[4] = in[i] / GAIN;
        yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4];
        yv[4] =   (xv[0] + xv[4]) - 2 * xv[2]
                     + ( -0.8948743446 * yv[0]) + (  3.6561008557 * yv[1])
                     + ( -5.6264262396 * yv[2]) + (  3.8650558972 * yv[3]);
        out[i] = yv[4];
      }
  }



