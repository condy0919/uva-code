#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

int main()
{
	string str;
	int n;
	bool no;
	stack<char> s;

	cin >> n;
	while (n-- > 0) {
		cin >> str;
		no = false;

		while (!s.empty())
			s.pop();

		if (str.length() % 2 == 1)
			no = true;
		for (int i = 0; i < str.length() && !no; ++i) {
			if (str[i] == '(' || str[i] == '[')
				s.push(str[i]);
			else {
				if (s.empty() || (s.top() != '(' && s.top() != '['))
					no = true;
				else
					s.pop();
			}
		}
		cout << (no?"No":"Yes");
		//if (n)
			cout << endl;
	}
	return 0;
}
