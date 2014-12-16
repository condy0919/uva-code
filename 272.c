#include <stdio.h>
#include <ctype.h>

int main() {
    int ch, q = 1;
    while ((ch = getchar()) != EOF) {
        if (ch != '\"') {
            putchar(ch);
        } else {
            printf("%s", q ? "``" : "''");
            q = !q;
        }
    }
    return 0;
}
