#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <numeric>

using namespace std;

/*
 * 一开始没有考虑到当中可能会有不匹配的情况。。
 */

bool check(const vector<int>& vec, int& size)
{
	if (vec.size() == 0) {
		size = 0;
		return true;
	}

	size = vec.back();
	int internal_size = 0, t;
	int i, j;

	for (i = 1, j = i + 1; j < vec.size(); ++j) {
		if (vec[i] == -vec[j] && i != j) {
			bool ret = check(vector<int>(vec.begin()+i, vec.begin()+j+1), t);
			if (!ret)
				return false;
			internal_size += t;
			if (internal_size >= size)
				return false;
			i = j + 1;
		}
	}
	return accumulate(vec.begin(), vec.end(), 0) == 0;
}

int main()
{
	string str;
	int x, size;

	while (getline(cin, str)) {
		vector<int> vec;
		istringstream iss(str);

		while (iss >> x)
			vec.push_back(x);
		if (check(vec, size))
			cout << ":-) Matrioshka!" << endl;
		else
			cout << ":-( Try again." << endl;
	}
	return 0;
}
