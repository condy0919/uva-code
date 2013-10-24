#include <stdio.h>
#include <stdlib.h>

char str[13];
char left[7], right[7];

int match(int p1,int p2,int p3,int p4,int p5,int p6)
{
	/* 1,2,3,4,5,6
	 1,3,5,2,4,6
	 1,5,4,3,2,6
	 1,4,2,5,3,6 */
	
	if (left[1]==right[p1] && left[2]==right[p2] && left[3]==right[p3]&&
			left[4]==right[p4] && left[5]==right[p5] && 
			left[6]==right[p6])
		return 1;

	if (left[1]==right[p1] && left[2]==right[p3] && left[3]==right[p5]&&
			left[4]==right[p2] && left[5]==right[p4] && 
			left[6]==right[p6])
		return 1;

	if (left[1]==right[p1] && left[2]==right[p5] && left[3]==right[p4]&&
			left[4]==right[p3] && left[5]==right[p2] && 
			left[6]==right[p6])
		return 1;

	if (left[1]==right[p1] && left[2]==right[p4] && left[3]==right[p2]&&
			left[4]==right[p5] && left[5]==right[p3] && 
			left[6]==right[p6])
		return 1;
	return 0;
}

int main()
{
	int i;

	while (scanf("%s", str) == 1) {
		for (i = 0; i < 6; ++i)
			left[i+1] = str[i];
		for (i = 6; i < 12; ++i)
			right[i - 5] = str[i];
		/* part done */

		if (match(1,2,3,4,5,6)||match(2,1,4,3,6,5)||
				match(3,2,6,1,5,4)||match(4,2,1,6,5,3)||
				match(5,1,3,4,6,2)||match(6,5,3,4,2,1))
			puts("TRUE");
		else
			puts("FALSE");
	}
	return 0;
}
