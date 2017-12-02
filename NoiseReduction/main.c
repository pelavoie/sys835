/*
 * main.c
 */
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "filter.h"
#include "noisedetector.h"
#include "energy.h"

short data[160];
float input[160];
float output[160];


int main(void) {
	int i, j;
	unsigned cnt=0;
	FILE* rid = fopen("car.raw","rb");
	FILE* wid = fopen("out.raw","wb");
	if ((rid == NULL) || (wid == NULL))
	{
		return -1;
	}
	// read
	size_t n = fread(data, sizeof(short), 160, rid);
	if (n !=160)
	{
		return -1;
	}
	do
	{
		// frame energy
		unsigned energy = sumsq(data, 160);
		unsigned threshold = noisedetector(energy);
		int frame_is_noise = energy < threshold;
		if (frame_is_noise)
		cnt++;
		// convert input to float
		for (i=0; i<160; i++)
		{
			input[i] = (float)(data[i]/32768.0);
		}
		// clear data
		for (i=0; i<160; i++)
		{
			data[i] = 0;
		}
		// filter: separate signal into 17 channels
		for (j=0; j<17; j++)
		{
			filterN2(output, input, b[j], gains[j], 160);

			// compute channel energy

			if (frame_is_noise)
			{
				// Compute Noise with smoothing (1 sec. noise frames)
			}
			else
			{
				// Compute Noise
			}

			// Détermination du gain

	        // Application du gain

//			% Recombinaison signaux des canaux
//	        % avec un déphasage de 180° entre eux.

			// convert output back to short and combine
			for (i=0; i<160; i++)
			{
				if (i%2==0)
				{
					data[i] += (short)(output[i]*32768.0);
				}
				else
				{
					data[i] -= (short)(output[i]*32768.0);
				}
			}
		}
		// write
		if (fwrite(data, sizeof(short), 160, wid) != 160)
		{
			return -1;
		}
		n = fread(data, sizeof(short), 160, rid);
	} while(n==160);
	int eof = feof(rid);
	int err = ferror(rid);
	fclose(rid);
	fclose(wid);
//	printf("%d\n",cnt);
	return 0;
}
