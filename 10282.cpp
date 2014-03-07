#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>

using namespace std;

int main()
{
	string line, en, oth;
	map<string, string> ref;

	while (getline(cin, line), !line.empty()) {
		istringstream iss(line);
		iss >> en >> oth;
		ref[oth] = en;
	}
	while (cin >> oth) {
		if (ref.find(oth) != ref.end())
			cout << ref[oth] << endl;
		else
			cout << "eh" << endl;
	}
	return 0;
}
