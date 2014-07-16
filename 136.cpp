#include <iostream>
#include <limits>

using namespace std;

/*
 * f[i]代表i个满足因子只有2、3、5性质的数。那f[i+1]必然也只有2,3,5这三个因子。
 * 则f[i+1]必然可由前面的f[1,2...i]乘上2、3、5推导出来。
 */

int ugly[1500] = {1,2,3,4,5};

int main() {
    for (int i = 5; i < 1500; ++i) {
        int next = numeric_limits<int>::max();
        for (int j = 0; j < i; ++j) {
            int next2 = ugly[j] * 2, next3 = ugly[j] * 3, next5 = ugly[j] * 5;
            if (next2 > ugly[i - 1])
                next = min(next, next2);
            if (next3 > ugly[i - 1])
                next = min(next, next3);
            if (next5 > ugly[i - 1])
                next = min(next, next5);
        }
        ugly[i] = next;
    }
    cout << "The 1500'th ugly number is " << ugly[1500 - 1] << "." << endl;
    return 0;
}
