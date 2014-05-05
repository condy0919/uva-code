#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>

/*
 * 和coursera的某次programming assignment很像。不过coursera上是用java实现的，转到C++后浮点精度各种问题。
 */

#define eps 1e-6

using namespace std;

struct point {
	int x, y;
	
	point() {}
	point(int _x, int _y):x(_x), y(_y) {}

	double slope(const point& p) {
		double dy = p.y - y, dx = p.x - x;
		if (fabs(dx) < eps)
			return numeric_limits<double>::infinity();
		return dy / dx;
	}

	bool equal_slope(const point& a, const point& b) {
		double sa = slope(a), sb = slope(b);
		if (sa == numeric_limits<double>::infinity() && sb == numeric_limits<double>::infinity())
			return true;
		else if (sa == numeric_limits<double>::infinity() || sb == numeric_limits<double>::infinity())
			return false;
		return fabs(sa - sb) < eps;
	}
};


struct cmpobj {
	point p;
	cmpobj(const point& _p) {
		p = _p;
	}

	bool operator()(const point& a, const point& b) {
		double sa = p.slope(a), sb = p.slope(b);
		if (sa == numeric_limits<double>::infinity() && sb == numeric_limits<double>::infinity())
			return false;
		else if (sa == numeric_limits<double>::infinity())
			return false;
		else if (sb == numeric_limits<double>::infinity())
			return true;
		return sa < sb;
	}
};

bool cmp(const point& a, const point& b) {
	if (a.y < b.y)
		return true;
	if (a.y > b.y)
		return false;
	return a.x < b.x;
}

int main()
{
	int T;
	int x, y;
	string s;

	cin >> T;
	cin.ignore();
	getline(cin, s);
	while (T-- > 0) {
		vector<point> pv;
		while (getline(cin, s) && !s.empty()) {
			istringstream iss(s);
			iss >> x >> y;
			pv.push_back(point(x, y));
		}
		int _max = 2;
		sort(pv.begin(), pv.end(), cmp);
		for (int i = 0; i < pv.size() - 1; ++i) {
			vector<point> copy = pv;
			sort(copy.begin() + i + 1, copy.end(), cmpobj(copy[i]));

			int head = i + 1, tail = i + 2;
			while (head < copy.size()) {
				while (tail < copy.size() && copy[i].equal_slope(copy[head], copy[tail]))
					++tail;
				_max = max(_max, tail - head + 1);
				head = tail++;
			}
		}
		cout << _max << endl;
		if (T)
			cout << endl;
	}
	return 0;
}
