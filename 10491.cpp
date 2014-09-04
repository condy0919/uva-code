#include <cstdio>

/*
 * 分类讨论： 在选手选择COW时，一种情况；
 *            在选手选择CAR时，另一种情况；
 */

using namespace std;

int main() {
    int NCOWS, NCARS, NSHOW;
    while (scanf("%d%d%d", &NCOWS, &NCARS, &NSHOW) == 3) {
        int N = NCOWS + NCARS;
        double ans = 1.0 * (NCOWS + NCARS - 1) * NCARS / (N * (N - NSHOW - 1));
        printf("%.5lf\n", ans);
    }

    return 0;
}
