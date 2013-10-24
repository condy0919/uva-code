#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;

char type[5] = {'+', '-', '?', '*','%'};

int calc(const string& s)
{
	int len;

	if (s == "1" || s == "4" || s == "78")
		return 0;
	
	len = s.length();
	if (len > 2 && s[len-1]=='5' && s[len-2]=='3')
		return 1;
	if (len > 3 && s[0]=='1'&&s[1]=='9'&&s[2]=='0')
		return 2;
	if (len > 2 && s[0]=='9'&&s[len-1]=='4')
		return 3;
	return 4;
}

int main()
{
	int n;
	string s;
	
	cin >> n;
	while (n-- > 0) {
		cin >> s;

		int ns = calc(s);
		putchar(type[ns]);
		putchar('\n');
	}
	return 0;
}

