#include <iostream>
#include <map>
#include <algorithm>
#include <string>


using namespace std;

int main()
{
	map< string, map<string, int> > lst;
	int n;
	string country, name;

	cin >> n;
	cin.ignore();
	for (int i = 0; i < n; ++i) {
		cin >> country;
		cin.ignore();
		getline(cin, name);
		lst[country][name]++;
	}

	map< string, map<string, int> >::iterator iter;
	for (iter = lst.begin(); iter != lst.end(); ++iter)
		cout << iter->first << " " << iter->second.size() << endl;

	return 0;
}

