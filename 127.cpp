#include <iotream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef struct elem_t {
	char color;
	int v;
	elem_t(char _c, int _v):color(_c), v(_v) {}
} elem_t;

int c2int(char ch)
{
	if (ch == 'A')
		return 1;
	if (ch <= 'K' && ch >= 'J')
		return 11 + ch - 'J';
	if (ch == 'T')
		return 10;
	return ch - '0';
}

int main()
{
	string str;
	vector<elem_t> vec;
	int i;

	while (true) {
		for (int i = 0; i < 52; ++i) {
			cin >> str;
			if (str[0] == '#')
				return 0;
			vec.push_back(elem_t(str[1], c2int(str[0])));
		}

	}
	
	return 0;
}
