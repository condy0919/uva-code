#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

/*
 * 这次又在输出格式上错误了几次。
 * 同样的，自己也知道了它会有相同的序列。
 */

int main()
{
	int total_test;
	int n, i;
	string str;
	vector<string> ori, wanted;
	stack<string> S;
	bool same;

	cin >> total_test;
	while (total_test-- > 0) {
		cin >> n;
		cin.ignore();
		ori.clear();
		wanted.clear();
		for (i = 0; i < n; ++i) {
			getline(cin, str);
			ori.push_back(str);
		}
		for (i = 0; i < n; ++i) {
			getline(cin, str);
			wanted.push_back(str);
		}
		same = false;
		for (i = 0; i < ori.size(); ++i)
			if (ori[i] != wanted[i])
				break;
		if (i == ori.size())
			same = true;
		for (i = 0; !same; ++i) {
			string e = wanted[i];
			vector<string>::iterator iter = find(ori.begin(), ori.end(), e);
			S.push(e);
			ori.erase(iter);
			// check whether it is same
			int j;
			for (j = i + 1; j < wanted.size(); ++j)
				if (wanted[j] != ori[j - i - 1])
					break;
			if (j == wanted.size())
				same = true;
		}
		while (!S.empty()) {
			string s = S.top();
			S.pop();
			cout << s << endl;
		}
		cout << endl;
	}
	return 0;
}

