#include <iostream>
#include <algorithm>
#include <cfloat>
#include <cstdio>
#include <cmath>

/*
 * 一开始认为这题很简单，果断的WA了。。。原因在于没有考虑到有极小半径球的情况。
 * 在上述情况下，极小球可能并不对下一个球的x坐标有影响。
 * 因而我采用的方法是，在摆放第i个球时，计算它们分别到i球的水平距离+它们的x坐标。
 * 假设前i-1个球都是与i球相切，这样就不会漏掉1个可能性的解。例如2大球中间夹着多个小球的情况。
 * 同样的，真实情况下，只有与i球相切的球才会对i球的x坐标值产生影响。在应用了上面这种方法后，
 * Assumpation:
 * (假设i球前必有一大球与其相切）不相关的球的x坐标+假设相切时的圆心距离 始终是小于真实相切的球
 * 所带来的影响的。
 * （假设i球前全是极小球）则可能大球i会直接靠着最左边。
 * proof:
 *		Assumpation:假设对i球有影响的球j与i球不相切。
 *		在极限情况下j球会与i球中间隔着一小球且彼此相切。当中间的小球稍候变大一点后，j球即与i球不相切，
 *		此时在几何上也可以清楚地看出j球是不会对i球有影响的。距离i球距离更远的球与i球中间隔了更多的球，同样也
 *		不会影响i球。
 *		在第2种假设中，显然只有取大球的半径才可以。
 */

using namespace std;

double radii[8];
int n, m;
double _min;

inline double dist(int a, int b)
{
	return 2 * sqrt(radii[a] * radii[b]);
}

double get_size_of_box()
{
	double ret = 0.0;
	double partial_dis[8] = {radii[0]};
	double max_par_dis;
	int i, j;

	for (i = 1; i < m; ++i) {
		max_par_dis = 0.0;
		for (j = 0; j < i; ++j)
			max_par_dis = max(max_par_dis, partial_dis[j] + dist(i, j));
		partial_dis[i] = max(max_par_dis, radii[i]);
	}
	for (i = 0; i < m; ++i)
		ret = max(ret, partial_dis[i] + radii[i]);
	return ret;
}

int main()
{
	cin >> n;
	while (n-- > 0) {
		cin >> m;
		for (int i = 0; i < m; ++i)
			cin >> radii[i];

		_min = DBL_MAX;
		sort(radii, radii + m);
		do {
			_min = min(get_size_of_box(), _min);
		} while (next_permutation(radii, radii + m));
		printf("%.3lf\n", _min);
	}
	return 0;
}
