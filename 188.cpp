#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int VAL(const string& s)
{
	int ret = 0;
	for (int i = 0; i < s.length(); ++i)
		ret = 32 * ret + (s[i] - 'a' + 1);
	return ret;
}

int calc(const string& line)
{
	istringstream iss(line);
	string s;
	vector<int> vec;

	while (iss >> s)
		vec.push_back(VAL(s));
	int c = *min_element(vec.begin(), vec.end());
	bool ok;
	do {
		ok = true;
		for (int i = 0; i < vec.size(); ++i)
			for (int j = i + 1; j < vec.size(); ++j) {
				int a = c/vec[i], b = c/vec[j];
				if (a % vec.size() == b % vec.size()) {
					ok = false;
					c = min((a + 1) * vec[i], (b + 1) * vec[j]);
				}
			}
	} while (!ok);
	return c;
}

int main()
{
	string line;
	while (getline(cin, line), !line.empty()) {
		cout << line << endl;
		cout << calc(line) << endl << endl;
	}
	return 0;
}
