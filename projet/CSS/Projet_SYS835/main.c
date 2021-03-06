/*
 * main.c
 */
#include <stdio.h>
#include "include/algorithm.h"

void main(void) {
	size_t n;

	/* Open car.raw to produce Frames of data*/
	FILE* rid = fopen("../data/car.raw","rb");
	FILE* wid = fopen("../data/out.raw","wb");
	if ((rid == NULL) || (wid == NULL))
		return;

	do
	{
		tRAW_FRAME InputRawData;
		tRAW_FRAME OutputData;

		// Read one frame
		n = fread(InputRawData, sizeof(short), NUMBER_OF_SAMPLES_PER_FRAME, rid);
		if (n !=NUMBER_OF_SAMPLES_PER_FRAME)
		{
			break;
		}

		//Compute Frame
		NoiseSuppressionAlgorithm((const tRAW_FRAME *)&InputRawData, &OutputData);

		// Save Output
		if (fwrite(OutputData, sizeof(short), NUMBER_OF_SAMPLES_PER_FRAME, wid) != NUMBER_OF_SAMPLES_PER_FRAME)
		{
			break;
		}
	} while(n==NUMBER_OF_SAMPLES_PER_FRAME);

	int eof = feof(rid);
	int err = ferror(rid);
	fclose(rid);
	fclose(wid);
	return;
}
