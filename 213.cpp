#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

char codes[8][1 << 8];

char readchar() {
    int ch;
    do {
        ch = getchar();
    } while (ch == '\n' || ch == '\r');
    return ch;
}

int readint(int cnt) {
    int ret = 0;
    while (cnt-- > 0)
        ret = 2 * ret + (readchar() - '0');
    return ret;
}

int readlen() { return readint(3); }

int main() {
    while (true) {
        memset(codes, 0, sizeof(codes));
        for (int i = 1; i < 8; ++i) {
            for (int j = 0; j < (1 << i) - 1; ++j) {
                int ch = getchar();
                if (ch == '\n')
                    goto fin;
                else if (ch == EOF)
                    return 0;
                codes[i][j] = ch;
            }
        }
fin:
        while (int len = readlen()) {
            int val;
            while ((val = readint(len)) != (1 << len) - 1)
                putchar(codes[len][val]);
        }
        puts("");
        if (getchar() == EOF)
            return 1;
    }
    return 0;
}
