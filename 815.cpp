#include <cstdio>
#include <algorithm>

using namespace std;

int block[900];
int n;
int total;

int main() {
    int a, b;
    int region = 0;
    while (scanf("%d%d", &a, &b), a && b) {
        n = a * b;
        printf("Region %d\n", ++region);
        for (int i = 0; i < n; ++i)
            scanf("%d", &block[i]);
        scanf("%d", &total);

        sort(block, block + n);
        double h = block[0], water = 0.0;
        for (int i = 1; i < n; ++i) {
            int diff = (block[i] - block[i - 1]) * i * 100;
            if (diff + water <= total) {
                water += diff;
                h = block[i];
            } else {
                h += (total - water) / 100.0 / i;
                water = total;
                break;
            }
        }
        if (water < total)
            h += (total - water) / 100.0 / n;
        printf("Water level is %.2lf meters.\n", h);
        printf("%.2lf percent of the region is under water.\n\n",
               100.0 *
                   count_if(block, block + n, [h](int x) { return x < h; }) /
                   n);
    }

    return 0;
}
