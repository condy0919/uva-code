#include <iostream>
#include <algorithm>
#include <cstdio>

/*
 * 还是贪心啊。主要是对区间范围的更新问题。
 */

using namespace std;

int b, s;
int n[20005];

int main()
{
    cin >> b;
    for (int route = 1; route <= b; ++route) {
        cin >> s;
        for (int i = 1; i < s; ++i)
            cin >> n[i];
        int sum = 0;
        int left = 1, max = -0x7fffffff;
        int beg = 1, end = 1;
        for (int i = 1; i < s; ++i) {
            sum += n[i];
            if (sum > max || sum == max && (i - left > end - beg)) { // 后面的那句没有写，导致一直没有更新长度
                max = sum;

                end = i;
                beg = left;
            }
            if (sum < 0) {
                sum = 0;
                left = i + 1;
            }
        }
        if (max <= 0)
            printf("Route %d has no nice parts\n", route);
        else
            printf("The nicest part of route %d is between stops %d and %d\n", route, beg, end + 1);
    }
    return 0;
}
