#include <cstdio>

using namespace std;

int main() {
    int testcases;
    int D, I;
    scanf("%d", &testcases);
    while (testcases-- > 0) {
        scanf("%d %d", &D, &I);
        int pos = 1;
        for (int i = 1; i < D; ++i) {
            if (I % 2) {
                pos = 2 * pos;
                I = (I + 1) / 2;
            } else {
                pos = 2 * pos + 1;
                I = I / 2;
            }
        }
        printf("%d\n", pos);
    }
    scanf("-1");
    return 0;
}
