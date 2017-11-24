/*
 * main.c
 */
#include <stdio.h>

void filterN2(float* out, float* in, float* a, float* b, unsigned nb);

int main(void) {
	short data[160];
	float input[160];
	float output[160];
	int i;
	FILE* fid = fopen("car.bin","r");
	if (fid == NULL)
	{
		return -1;
	}
	int cnt = fread(data, sizeof(float), 160, fid);
	if (cnt!=160)
	{
		return -1;
	}
	for (i=0; i<160; i++)
	{
		input[i] = (float)(data[i]/32768.0);
	}
	filterN2(output, input, 0, 0, 160);
	fclose(fid);
	return 0;
}
