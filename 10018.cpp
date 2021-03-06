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
#include <stdint.h>

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

	void clean() {
		while (len > 1 && !s[len - 1])
			--len;
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

	bign operator * (const int b) {
		char v[100];
		bign c;
		sprintf(v, "%d", b);

		c = v;
		return *this * c;
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

	// default: current number >= b
	bign operator / (const int b) {
		bign t = *this;
		string result;
		int i, j;
		int64_t divided_number = 0;
		int quotient, remainder;

		for (i = 0, j = t.len-1; i < j; ++i, --j)
			swap(t.s[i], t.s[j]);

		// find first part
		for (j = 0; j < t.len && divided_number < b; ++j)
			divided_number = 10 * divided_number + t.s[j];
		quotient = divided_number / b;
		remainder = divided_number % b;
		result += (char)(quotient + '0');
		for (int k = j - 1; k >= 0; --k) {
			t.s[k] = remainder % 10;
			remainder /= 10;
		}
		
		// the remaining part
		for (i = 0; i < t.len && j < t.len; /*++i,*/ ++j) {
			divided_number = 0;
			while (i < t.len && !t.s[i])
				++i;
			for (int k = i; k <= j; ++k)
				divided_number = 10 * divided_number + t.s[k];
			while (j < t.len && divided_number < b) {
				result += '0';
				divided_number = 10 * divided_number + t.s[++j];
			}
			quotient = divided_number / b;
			remainder = divided_number % b;
			if (j < t.len)
				result += (char)(quotient + '0');

			for (int k = j; k >= i; --k) {
				t.s[k] = remainder % 10;
				remainder /= 10;
			}
		}

		//for (i = result.length() - 1; i >= 0 && result[i] == '0'; --i)
		//	result.erase(i);
		return bign(result.c_str());
	}

	bign operator % (const int b) {
		bign ret;
		ret = *this - (*this / b) * b;
		return ret;
	}

	bool operator < (const bign& b) const {
		if (len != b.len)
			return len < b.len;
		for (int i = len - 1; i >= 0; --i)
			if (s[i] != b.s[i])
				return s[i] < b.s[i];
		return false;
	}

	bool operator < (const int x) const {
		return *this < bign(x);
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

bool is_palindrome(const bign& num) {
	int i, j;
	for (i = 0, j = num.len - 1; i < j; ++i, --j)
		if (num.s[i] != num.s[j])
			return false;
	return true;
}

void reverse_bign(bign& num) {
	int i;
	for (i = 0; i < num.len/2; ++i)
		swap(num.s[i], num.s[num.len - 1 - i]);
}

int main()
{
	bign a, b;
	int n;
	int cnt;
	
	cin >> n;
	while (n-- > 0) {
		cnt = 0;
		cin >> a;

		while (!is_palindrome(a)) {
			b = a;
			reverse_bign(a);
			a = a + b;
			++cnt;
		}
		cout << cnt << ' ' << a << endl;
	}
	return 0;
}

