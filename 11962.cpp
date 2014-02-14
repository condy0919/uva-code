#include <iostream>
#include <string>
#include <algorithm>
#include <stdint.h>

using namespace std;

// A, C, G, T
uint64_t fun(char ch)
{
	if (ch == 'A')
		return 0 ;
	if (ch == 'C')
		return 1;
	if (ch == 'G')
		return 2;
	return 3;
}

uint64_t solve(const string& s)
{
	uint64_t ret = 0;

	for (int i = 0; i < s.length(); ++i)
		ret = 4 * ret + fun(s[i]);
	return ret;
}

int main()
{
	int n;
	string s;

	cin >> n;
	for (int cases = 1; cases <= n; ++cases) {
		cin >> s;

		cout << "Case " << cases << ": " << "(" << s.length() << ":"
			<< solve(s) << ")\n";
	}

	return 0;
}
