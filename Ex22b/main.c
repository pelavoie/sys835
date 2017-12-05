
#include "DSK6713_aic23.h"
#include "DSK6713_led.h"
#include "algorithm.h"

Uint32 fs=DSK6713_AIC23_FREQ_8KHZ;

#define DSK6713_AIC23_INPUT_LINE 0x0011
Uint16 inputsource=DSK6713_AIC23_INPUT_LINE;

void 	comm_intr();
void 	output_left_sample(short);
short 	input_left_sample();

#define N 160
short   ping = 0;
short 	buffercount = 0;
short 	In_1[N], In_2[N];
short Out_1[N] = {0};
short Out_2[N] = {0};

void maFontion(short *inbuf, short *outbuf);

interrupt void c_int11(void)
{
	if(ping == 0)
	{
//		output_left_sample((short)(Out_1[buffercount]*32768.0));
//		In_1[buffercount] = (float)(input_left_sample()/32768.0);
		output_left_sample((Out_1[buffercount]));
		In_1[buffercount] = (input_left_sample());
		buffercount += 1;
	} else
	{
//		output_left_sample((short)(Out_2[buffercount]*32768.0));
//		In_2[buffercount] = (float)(input_left_sample()/32768.0);
		output_left_sample((Out_2[buffercount]));
		In_2[buffercount] = (input_left_sample());
		buffercount += 1;
	}

	if (buffercount >= N)
	{
		buffercount = 0;
		if (ping == 0)
		{
			ping = 1;
			DSK6713_LED_on(0);
			DSK6713_LED_off(1);
		}
		else
		{
			ping = 0;
			DSK6713_LED_on(1);
			DSK6713_LED_off(0);
		}
	}
}

void maFontion(short *inbuf, short *outbuf)
{
    int i = 0;

// Votre traitement

    for (i = 0; i < N; i++)
    {
		outbuf[i]  = inbuf[i];
    }
// Fin de traitement

}


main()
{
  comm_intr();
  DSK6713_LED_off(0);
  DSK6713_LED_off(1);
  DSK6713_LED_off(2);
  DSK6713_LED_off(3);
  int i;

  while(1)
  {
	if(ping == 0)
	{
		  for (i=0; i<N; i++)
		  {
			  Out_2[i] = 0;
		  }
		NoiseSuppressionAlgorithm((const tRAW_FRAME*)In_2, (tRAW_FRAME*)Out_2);
//		maFontion(In_2, Out_2);
	}
	 else
	 {
		  for (i=0; i<N; i++)
		  {
			  Out_1[i] = 0;
		  }
		 NoiseSuppressionAlgorithm((const tRAW_FRAME*)In_1, (tRAW_FRAME*)Out_1);
//		 maFontion(In_1, Out_1);
	 }
  }

}

