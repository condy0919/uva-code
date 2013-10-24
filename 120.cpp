#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	string line;
	vector<int> vec;

	while (getline(cin, line) && line.length() > 0) {
		istringstream iss(line);

		cout << line << endl;
		int x;

		vec.clear();
		while (iss >> x)
			vec.push_back(x);

		reverse(vec.begin(), vec.end());
		vector<int>::iterator st;

		for (st = vec.begin(); st != vec.end(); ++st) {
			vector<int>::iterator m = max_element(st, vec.end());
			
			if (m == st)
				continue;

			if (m != vec.end() - 1) {
				reverse(m, vec.end());
				cout << m - vec.begin() + 1 << ' ';
			}
			reverse(st, vec.end());
			cout << st - vec.begin() + 1 << ' ';
		}
		cout << '0' << endl;
	}
	return 0;
}

