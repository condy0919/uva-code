#include <stdio.h>

/*
 * 感谢http://www.cnblogs.com/staginner/archive/2011/12/08/2281371.html
 * 让我知道了还有更简单的方法。
 * 偑尔方程：用连分数求得浙近分数，求得一个non-trival的解。
 * 后利用递推关系 \
 *   x_{k+1}      x_1    n*y_1     x_k
 *  [       ] = [             ] * [   ]
 *   y_{k+1}      y_1    x_1       y_k
 */

#define n 8

int i;
int x1 = 3, y1 = 1;
int x = 3, y = 1;

int main() {
    for (i = 0; i < 10; ++i) {
        int _x = x * x1 + y * n * y1,
            _y = x * y1 + y * x1;
        x = _x, y = _y;
        printf("%10d%10d\n", y, (x - 1) / 2);
    }
    return 0;
}
