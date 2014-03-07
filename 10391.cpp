#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
	istream_iterator<string> cin_it(cin), eof;
	set<string> store(cin_it, eof);

	typedef set<string>::iterator iter;
	for (iter i = store.begin(); i != store.end(); ++i) {
		for (int j = 1; j < i->length() - 1; ++j) {
			const string& a = i->substr(0, j);
			const string& b = i->substr(j);
			if (store.count(a) && store.count(b)) {
				cout << *i << endl;
				break;
			}
		}
	}
	return 0;
}
