/*
 * main.c
 */

short child (short *, short *, short );
short child1 (short *, short *, short );

short z;
short w[3] = {1, 2, 3};
short x[3] = {10, 20, 30};
short y[3] = {40, 50, 60};

int main(void ) {
	short n=3;
	z = child(x, y, n);
	return z;
}
