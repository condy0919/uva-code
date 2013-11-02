#include <stdio.h>
#include <stdlib.h>

/*
 * 群论
 */

int abs(int x)
{
	return (x>0)?x:-x;
}

#define min(a,b) ((a)<(b)?(a):(b))

int kgcd(int a, int b)
{
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	if (!(a & 1) && !(b & 1))
		return kgcd(a >> 1, b >> 1) << 1;
	else if (!(b & 1))
		return kgcd(a, b >> 1);
	else if (!(a & 1))
		return kgcd(a >> 1, b);
	return kgcd(abs(a-b), min(a, b));
}

int main()
{
	int a, b;
	
	while (scanf("%d%d", &a, &b) == 2){
		if (kgcd(a, b) == 1)
			printf("%10d%10d    Good Choice\n\n", a, b);
		else
			printf("%10d%10d    Bad Choice\n\n", a, b);
	}
	return 0;
}

