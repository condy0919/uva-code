#include <iostream>
#include <algorithm>
#include <string>

/*
 * 越简单的题真是越会错啊。。。
 * 输出格式又错了。。。
 */

using namespace std;

int main()
{
	int T;
	string s;

	cin >> T;
	while (T-- > 0) {
		cin >> s;
		sort(s.begin(), s.end());

		do {
			cout << s << endl;
		} while (next_permutation(s.begin(), s.end()));
		cout << endl;
	}
	return 0;
}
