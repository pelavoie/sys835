
#include <stdio.h>
#include "../include/main_func.h"
#include "../include/algorithm.h"

int MainTest()
{
	tFRAME InputData;
	tFRAME OutputData;

	FILE* rid = fopen("../data/car.raw","rb");
	FILE* wid = fopen("../data/out.raw","wb");
	if ((rid == NULL) || (wid == NULL))
	{
		return -1;
	}
	// read
	size_t n = fread(InputData, sizeof(short), NUMBER_OF_SAMPLES_PER_FRAME, rid);
	if (n !=NUMBER_OF_SAMPLES_PER_FRAME)
	{
		return -1;
	}

	do
	{
		NoiseSuppressionAlgorithm(&InputData, &OutputData);

		// write
		if (fwrite(OutputData, sizeof(short), NUMBER_OF_SAMPLES_PER_FRAME, wid) != NUMBER_OF_SAMPLES_PER_FRAME)
		{
			return -1;
		}
		n = fread(InputData, sizeof(short), NUMBER_OF_SAMPLES_PER_FRAME, rid);
	} while(n==NUMBER_OF_SAMPLES_PER_FRAME);

	int eof = feof(rid);
	int err = ferror(rid);
	fclose(rid);
	fclose(wid);
//	printf("%d\n",cnt);
	return 0;
}
