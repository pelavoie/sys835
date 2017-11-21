extern short w[3];
short child(short *a, short *b, short n)
{
	int i;
	short c=0;

	for(i=0; i<n; i++)
	{
		c += w[i] * a[i] - b[i];
	}
	return c;
}
