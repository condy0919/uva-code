#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

struct xy_t {
	int x, y;
};

int n;
double _min;
int ans[8];
xy_t points[8];

double dist(const xy_t& a, const xy_t& b)
{
	return sqrt(pow(a.x-b.x, 2.0) + pow(a.y-b.y, 2.0)) + 16.0;
}

double dis(int arrange[])
{
	int i;
	double s = 0.0;

	for (i = 0; i < n - 1; ++i)
		s += dist(points[arrange[i]], points[arrange[i+1]]);
	return s;
}

int main()
{
	int x, y;
	int round = 0;

	while (cin >> n, n) {
		for (int i = 0; i < n; ++i) {
			cin >> x >> y;
			points[i].x = x;
			points[i].y = y;
		}
		int arrange[8] = {0,1,2,3,4,5,6,7};
		_min = 150 * 8.0;
		do {
			if (dis(arrange) < _min) {
				_min = dis(arrange);
				copy(arrange, arrange + n, ans);
			}
		} while (next_permutation(arrange, arrange + n));
		cout << "**********************************************************" << endl;
		cout << "Network #" << ++round << endl;
		for (int i = 0; i < n - 1; ++i)
			printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2lf feet.\n", points[ans[i]].x, points[ans[i]].y, points[ans[i+1]].x, points[ans[i+1]].y, dist(points[ans[i]], points[ans[i+1]]));
		printf("Number of feet of cable required is %.2lf.\n", _min);
	}
	return 0;
}
