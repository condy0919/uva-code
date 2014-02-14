#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

#define BASE 10000
#define GAP	 4

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
		int l = strlen(num);
		int i;
		char src[GAP];

		len = ceil((double)l / GAP);
		for (i = 0; i < l - GAP; i += GAP) {
			int st = l - i - GAP;

			strncpy(src, num + st, GAP);
			s[i/GAP] = atoi(src);
		}
		int rem = l - i;
		strncpy(src, num, rem);
		src[rem]='\0';
		s[i/GAP] = atoi(src);

		return *this;
	}

	string str() const {
		string res = "";
		char src[GAP];
		for (int i = 0; i < len - 1; ++i)
			for (int j = 0, t = s[i]; j < GAP; ++j, t /= 10)
				res = (char)(t%10 + '0') + res;

		sprintf(src, "%d", s[len - 1]);
		res = src + res;
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
			c.s[c.len++] = x % BASE;
			g = x / BASE;
		}
		return c;
	}

	void clean() {
		while (len > 1 && !s[len - 1])
			--len;
	}

	bign operator * (const bign& b) {
		bign c;
		c.len = len + b.len + 1;

		for (int i = 0; i < len; ++i)
			for (int j = 0; j < b.len; ++j) {
				c.s[i + j] += s[i] * b.s[j];
				c.s[i + j + 1] += c.s[i + j] / BASE;
				c.s[i + j] %= BASE;
			}
		c.clean();
		return c;
	}

	// need current number >= b
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
				x += BASE;
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

	bign operator *= (const bign& b) {
		*this = *this * b;
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
	string x;
	int n, leap;

	while (cin >> x >> n) {
		leap = 0;
		if (x.find('.') != string::npos) {
			leap = 6 - x.find('.') - 1;
			x.erase(find(x.begin(), x.end(), '.'));
		}

		bign number(x.c_str());
		number.clean();
		bign res("1");

		for (int i = 0; i < n; ++i)
			res *= number;
		string output(res.str());
		if (leap != 0) {
			if (n * leap > output.length()) {
				int d = n * leap - output.length();
				output.insert(0, d, '0');
				output.insert(output.begin(), '.');
			} else
				output.insert(output.begin() + output.length() - leap*n, '.');
		}
		while (output[output.length() - 1] == '0')
			output.erase(output.begin() + output.length() - 1);
		cout << output << endl;
	}


	return 0;
}

