
#include <stdio.h>
#include "../include/main_func.h"
#include "../include/algorithm.h"

int MainTest()
{
	tRAW_FRAME InputRawData;
	tRAW_FRAME OutputData;
	size_t n;

	/* Open car.raw to produce Frames of data*/
	FILE* rid = fopen("../data/car.raw","rb");
	FILE* wid = fopen("../data/out.raw","wb");
	if ((rid == NULL) || (wid == NULL))
		return -1;

	do
	{
		// Read one frame
		n = fread(InputRawData, sizeof(short), NUMBER_OF_SAMPLES_PER_FRAME, rid);
		if (n !=NUMBER_OF_SAMPLES_PER_FRAME)
		{
			break;
		}

		//Compute Frame
		NoiseSuppressionAlgorithm(&InputRawData, &OutputData);

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
//	printf("%d\n",cnt);
	return 0;
}



