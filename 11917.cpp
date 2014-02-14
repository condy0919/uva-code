#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

int N;
int d;
map<string, int> ref;

int main()
{
	int T;
	int days;
	string subject;

	cin >> T;
	for (int cases = 1; cases <= T; ++cases) {
		ref.clear();
		cin >> N;
		while (N-- > 0) {
			cin >> subject >> days;
			ref[subject] = days;
		}
		cin >> d >> subject;
		cout << "Case " << cases << ": ";
		if (ref.count(subject) == 0 || ref[subject] > d + 5)
			cout << "Do your own homework!\n";
		else if (ref[subject] <= d)
			cout << "Yesss\n";
		else 
			cout << "Late\n";
	}
	return 0;
}
