#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstdio>

using namespace std;

// P=10.5KW
double parse(string& str, int pos)
{
	double ret;
	const char* pstr;
	int i;

	i = pos + 2;
	pstr = str.c_str() + pos + 2;
	ret = atof(pstr);

	do {
		++i;
	} while (!isalpha(str[i]));

	if (str[i] == 'k')
		ret *= 1000.0;
	else if (str[i] == 'm')
		ret *= 0.001;
	else if (str[i] == 'M')
		ret *= 1000000.0;

	return ret;
}

int main()
{
	int k, lines;
	string str;
	bool is_u, is_i, is_p;
	double u, i, p;
	string::size_type pos;

	cin >> lines;
	cin.ignore();

	for (k = 0; k < lines; ++k) {
		is_u = is_i = is_p = false;
		getline(cin, str);

		cout << "Problem #" << k + 1 << endl;

		pos = 0;
		while ((pos = str.find("U=", pos)) != string::npos) {
			int j = pos + 2;

			while (!isalpha(str[j]))
				++j;
			if (str[j] == 'm' || str[j] == 'k' || str[j] == 'M')
				++j;
			if (str[j] == 'V') {
				is_u = true;
				u = parse(str, pos);
				break;
			}
			pos = j;
		}

		pos = 0;
		while ((pos = str.find("I=", pos)) != string::npos) {
			int j = pos + 2;

			while (!isalpha(str[j]))
				++j;
			if (str[j] == 'm' || str[j] == 'k' || str[j] == 'M')
				++j;
			if (str[j] == 'A') {
				is_i = true;
				i = parse(str, pos);
				break;
			}
			pos = j;
		}

		pos = 0;
		while ((pos = str.find("P=", pos)) != string::npos) {
			int j = pos + 2;

			while (!isalpha(str[j]))
				++j;
			if (str[j] == 'm' || str[j] == 'k' || str[j] == 'M')
				++j;
			if (str[j] == 'W') {
				is_p = true;
				p = parse(str, pos);
				break;
			}
			pos = j;
		}

		if (!is_u) {
			u = p / i;
			printf("U=%.2lfV\n", u);
		} else if (!is_i) {
			i = p / u;
			printf("I=%.2lfA\n", i);
		} else {
			p = i * u;
			printf("P=%.2lfW\n", p);
		}
		if (k != lines - 1)
			printf("\n");
	}
	return 0;
}

