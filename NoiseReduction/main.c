/*
 * main.c
 */
#include <stdio.h>
#include <stdint.h>
#include <math.h>

void filterN2(float* out, float* in, float* coeffs, float gain, unsigned nb);

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

short data[160];
float input[160];
float output[160];
unsigned noisedetector(unsigned energy);

unsigned sumsq(short* data, unsigned n)
{
	int i;
	unsigned v2=0;
	for (i = 0; i<n; i++)
	{
		v2+=(data[i]*data[i])>>15;
	}
	return v2;
}

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
