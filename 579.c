#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double calc(int hour, int minute)
{
	double theta1, theta2;
	double ret;

	theta1 = 6.0 * minute;
	theta2 = 30.0 * hour + minute/2.0;
	ret = fabs(theta1-theta2);

	if (ret > 180.0)
		return 360.0 - ret;
	return ret;
}

int main()
{
	int hour, minute;
	double ans;

	while (scanf("%d:%d", &hour, &minute) == 2) {
		if (hour == 0 && minute == 0)
			break;
		ans = calc(hour, minute);
		printf("%.3lf\n", ans);
	}
	return 0;
}
