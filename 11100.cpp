#include <iostream>
#include <algorithm>

using namespace std;

/*
 * 贪心的题没有思路啊，果然还是要先多观察解出的答案和序列有什么关系。
 */

int a[10000];
int main()
{
	int n;
	bool flag = true;

	while (cin >> n, n) {
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		if (flag)
			flag = false;
		else
			cout << endl;
		sort(a, a + n);
		int front, tail;
		int c = 1;
		for (front = 0; front < n; front = tail) {
			tail = front + 1;
			while (tail < n && a[tail] == a[front])
				++tail;
			c = max(c, tail - front);
		}
		cout << c << endl;
		for (int i = 0; i < c; ++i) {
			cout << a[i];
			for (int j = i + c; j < n; j += c)
				cout << " " << a[j];
			cout << endl;
		}
	}
	return 0;
}
