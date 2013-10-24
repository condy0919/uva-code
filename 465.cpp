#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
#include <climits>


#define PI acos(-1.0)
#define eps (1e-12)
#define L(X) (X<<1)
#define R(X) (X<<1|1)


using namespace std;

#define maxn 30000

struct bign {
	int len, s[maxn];

	bign() {
		memset(s, 0, sizeof(s));
		len = 1;
	}

	bign(int num) {
		*this = num;
	}

	bign(const char* num) {
		*this = num;
	}

	bign operator=(int num) {
		char s[maxn];
		sprintf(s, "%d", num);
		*this = s;
		return *this;
	}

	bign operator=(const char* num) {
		len = strlen(num);
		for (int i = 0; i < len; ++i)
			s[i] = num[len - 1 - i] - '0';
		return *this;
	}

	string str() const {
		string res = "";
		for (int i = 0; i < len; ++i)
			res = (char)(s[i] + '0') + res;
		if (res == "")
			res = "0";
		return res;
	}

	bign operator + (const bign& b) const {
		bign c;
		c.len = 0;

		for (int i = 0, g = 0; g || i < max(len, b.len); ++i) {
			int x = g;
			if (i < len)
				x += s[i];
			if (i < b.len)
				x += b.s[i];
			c.s[c.len++] = x % 10;
			g = x / 10;
		}
		return c;
	}

	void clean() {
		while (len > 1 && !s[len - 1])
			--len;
	}

	bign operator * (const bign& b) {
		bign c;
		c.len = len + b.len;

		for (int i = 0; i < len; ++i)
			for (int j = 0; j < b.len; ++j)
				c.s[i + j] += s[i] * b.s[j];
		for (int i = 0; i < c.len - 1; ++i) {
			c.s[i+1] += c.s[i] / 10;
			c.s[i] %= 10;
		}
		c.clean();
		return c;
	}

	bign operator - (const bign& b) {
		bign c;
		c.len = 0;

		for (int i = 0, g = 0; i < len; ++i) {
			int x = s[i] - g;
			if (i < b.len)
				x -= b.s[i];
			if (x >= 0)
				g = 0;
			else {
				g = 1;
				x += 10;
			}
			c.s[c.len++] = x;
		}
		c.clean();
		return c;
	}

	bool operator < (const bign& b) const {
		if (len != b.len)
			return len < b.len;
		for (int i = len - 1; i >= 0; --i)
			if (s[i] != b.s[i])
				return s[i] < b.s[i];
		return false;
	}

	bool operator > (const bign& b) const {
		return b < *this;
	}

	bool operator <= (const bign& b) const {
		return !(b > *this);
	}

	bool operator == (const bign& b) const {
		return !(b < *this) && !(*this < b);
	}

	bool operator != (const bign& b) const {
		return (b < *this) || (*this < b);
	}

	bign operator += (const bign& b) {
		*this = *this + b;
		return *this;
	}
};

istream& operator >> (istream& in, bign& x) {
	string s;

	in >> s;
	x = s.c_str();
	return in;
}

ostream& operator << (ostream& out, bign& x) {
	out << x.str();
	return out;
}


int main()
{
	bign a, b, Max = INT_MAX;
	char op;

	while (cin >> a >> op >> b) {
		cout << a << ' ' << op << ' ' << b << endl;

		a.clean();
		b.clean();
		if (a > Max)
			cout << "first number too big" << endl;
		if (b > Max)
			cout << "second number too big" << endl;

		if (op == '+' && a+b>Max)
			cout << "result too big" << endl;
		else if (op == '*' && a*b>Max)
			cout << "result too big" << endl;
	}
	return 0;
}

