#include <cstdio>
#include <algorithm>

/*
 * 简单题.找关系...
 */

using namespace std;

double p[16][16];

double exist(int id, int stage) {
    static double cache[16][4] = { 0 };

    if (cache[id][stage] != 0.0)
        return cache[id][stage];

    if (stage == 0) {
        int op = (id % 2 == 0) ? (id + 1) : (id - 1);
        return cache[id][stage] = p[id][op];
    }

    int scale = (1 << stage); // pow(2, stage)
    int t = id / scale;
    int op_start = scale * ((t % 2 == 0) ? (t + 1) : (t - 1));
    int a[scale];
    for (int i = 0, j = op_start; i < scale; ++i, ++j)
        a[i] = j;
    double ret = exist(id, stage - 1), s = 0;
    for (int i = 0; i < scale; ++i)
        s += exist(a[i], stage - 1) * p[id][a[i]];
    return cache[id][stage] = ret * s;
}

int main() {
    char nations[16][16] = {'\0'};
    for (int i = 0; i < 16; ++i)
        scanf("%s", nations[i]);
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            scanf("%lf", &p[i][j]);
            p[i][j] /= 100.0;
        }
    }

    for (int i = 0; i < 16; ++i)
        printf("%-10s p=%.2lf%\n", nations[i], 100 * exist(i, 3));

    return 0;
}
