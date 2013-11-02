#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define eps 1e-6

int main()
{
	int H, U, D, F;
	double k;
	double s = 0.0;
	int flag;
	int ans1, ans2;
	int k1;

	while (scanf("%d%d%d%d", &H, &U, &D, &F), H||U||D||F) {
		flag = 1;/* flag of success or failure */
		k = floor(((100.0 + F)*U-100.0*D)/(F * U));

		if (k <= 0)
			flag = 0;

		if (flag)
			s = k*U-F*U*k*(k-1)/200.0 - (k-1)*D;
		flag = (flag && s > H);
		if (flag) {
			ans1 = floor((200.0*U+F*U-200.0*D+sqrt(pow(200.0*U+F*U-200.0*D, 2)-800.0*F*U*(H-D)))/(2.0*F*U)-eps);
			ans2 = ceil((200.0*U+F*U-200.0*D-sqrt(pow(200.0*U+F*U-200.0*D, 2)-800.0*F*U*(H-D)))/(2.0*F*U)+eps);
			if (ans2 > 0)
				ans1 = ans2;
			printf("success on day %d\n", ans1);
		} else {
			k1 = ceil((100.0+F)/F);
			ans1 = ceil(200.0*(U-D)/(F*U)+1+eps);
			ans2 = ceil((200.0*k1*U-k1*(k1-1)*F*U)/(200.0*D)+eps);
			if (ans1 <= 0 || ans1 >= k1)
				ans1 = ans2;
			printf("failure on day %d\n", ans1);
		}
	}
	return 0;
}

