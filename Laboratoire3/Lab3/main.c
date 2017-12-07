/*
 * main.c
 */

short y_nooptimization(short *x, short* h, int n);
short y_parallel(short *x, short* h, int n);
short y_nopreplace(short *x, short* h, int n);
short y_unroll(short *x, short* h, int n);
short y_pipelined(short *x, short* h, int n);

short x[40];
short h[40];

int main(void) {
	int i=0;
	short y=0;
	short y0,y1,y2,y3,y4;
	for (i=0; i<40; i++)
	{
		x[i] = (2*i-70);
		h[i] = (28-3*i);
		y += x[i]*h[i];
	}
	y0 = y_nooptimization(x, h, 40);
	y1 = y_parallel(x, h, 40);
	y2 = y_nopreplace(x, h, 40);
	y3 = y_unroll(x, h, 40);
	y4 = y_pipelined(x, h, 40);
	return y;
}

