#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

/*
 * 本来这里写错了，直接是a>b.
 * 后来看到了1个反例9, 90，明显990较大。
 */
bool cmp(const string& a, const string& b) {
	return a + b > b + a;
}

int main()
{
	string s;
	vector<string> vec;
	int N;

	while (cin >> N, N) {
		vec.clear();
		for (int i = 0; i < N; ++i) {
			cin >> s;
			vec.push_back(s);
		}
		sort(vec.begin(), vec.end(), cmp);
		for (int i = 0; i < vec.size(); ++i)
			cout << vec[i];
		cout << endl;
	}

	return 0;
}

