#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	int total_test;
	string str1, str2;
	string s[5];

	cin >> total_test;
	cin.ignore();
	while (total_test-- > 0) {
		getline(cin, str1);
		getline(cin, str2);

		// print without <, >
		int cnt = 0;
		int i, j = 0;
		for (i = 0; cnt < 4; ++i)
			if (str1[i] == '<' || str1[i] == '>') {
				s[cnt++] = str1.substr(j, i - j);
				j = i + 1;
			} else
				cout << str1[i];
		s[cnt] = str1.substr(j);
		cout << s[4] << endl;

		int pos = str2.find("...");
		for (int k = 0; k < pos; ++k)
			cout << str2[k];
		cout << s[3] << s[2] << s[1] << s[4] << endl; 
	}
	return 0;
}
