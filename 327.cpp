#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;

int ref[26];
int refed[26];
bool vis[26];

void init()
{
	for (int i = 0; i < 26; ++i)
		ref[i] = refed[i] = i + 1;
	fill(vis, vis+sizeof(vis), false);
}

void trim(char* s)
{
	int len = strlen(s);
	int i, j;
	for (i = j = 0; i < len; ++i)
		if (s[i] != ' ')
			s[j++] = s[i];
	s[j] = '\0';
}

void trim(string& s)
{
	string::size_type pos = 0;
	pos = s.find(" ", pos);
	while (pos != string::npos) {
		s.replace(pos, 1, "");
		pos = s.find(" ", pos);
	}
}

void preprocess(string& exp)
{
	int i;

	for (i = 0; i < exp.length(); ++i) {
		if (!islower(exp[i]))
			continue;

		vis[exp[i] - 'a'] = true;
		if (i-2 >= 0 && exp[i-1] == exp[i-2]) {
			if (exp[i-1] == '+')
				refed[exp[i] - 'a'] = ++ref[exp[i] - 'a'];
			else
				refed[exp[i] - 'a'] = --ref[exp[i] - 'a'];
			exp[i-1] = exp[i-2] = ' ';
		}
		if (i+2 < exp.length() && exp[i+1] == exp[i+2]) {
			if (exp[i+1] == '+')
				refed[exp[i] - 'a'] = ref[exp[i] - 'a']++;
			else
				refed[exp[i] - 'a'] = ref[exp[i] - 'a']--;
			exp[i+1] = exp[i+2] = ' ';
		}
	}

}

int calc(const string& exp)
{
	int ret = refed[exp[0] - 'a'];
	int i;

	for (i = 1; i < exp.length(); i += 2)
		if (exp[i] == '+')
			ret += refed[exp[i+1] - 'a'];
		else
			ret -= refed[exp[i+1] - 'a'];
	return ret;
}

void output_var()
{
	int i;

	for (i = 0; i < 26; ++i)
		if (vis[i])
			cout << "    " << (char)(i + 'a') << " = " << ref[i] << endl;
}

int main()
{
	char str[120];

	while (cin.getline(str, sizeof(str))) {
		cout << "Expression: " << str << endl;

		init();
		trim(str);
		string exp(str);
		preprocess(exp);
		trim(exp);
		int ans = calc(exp);
		cout << "    value = " << ans << endl;
		output_var();
	}
	return 0;
}
