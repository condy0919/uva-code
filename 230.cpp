#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;
#define MAXD 1000 + 10
#define LEN 80 + 10
struct Book {
    char name[LEN];
    char author[LEN];
    friend bool operator<(Book p, Book q) {
        int e1 = strcmp(p.author, q.author);
        int e2 = strcmp(p.name, q.name);
        if (e1 != 0) {
            if (e1 > 0)
                return false;
            return true;
        } else {
            if (e2 > 0)
                return false;
            return true;
        }
    }
} book[MAXD];
int n = 0;
map<string, int> value;
int find_pre(int cur) {
    for (int i = cur - 1; i >= 0; i--) {
        if (value[book[i].name] == 1) return i;
    }
    return -1;
}
int main() {
    char str[LEN];
    int pos;
    value.clear();
    while (gets(str)) {
        if (strcmp(str, "END") == 0) break;
        pos = strchr(str + 1, '"') - str;
        strncpy(book[n].name, str, pos + 1);
        book[n].name[pos + 2] = '\0';
        pos = strstr(str + pos, "by") - str;
        strcpy(book[n].author, str + pos + 3);
        value[book[n].name] = 1;
        n++;
    }
    sort(book, book + n);
    while (scanf("%s", str)) {
        if (strcmp(str, "END") == 0) break;
        if (strcmp(str, "BORROW") == 0) {
            gets(str);
            value[str + 1] = 0;
        } else if (strcmp(str, "RETURN") == 0) {
            gets(str);
            value[str + 1] = 2;
        } else if (strcmp(str, "SHELVE") == 0) {
            for (int i = 0; i < n; i++)
                if (value[book[i].name] == 2) {
                    pos = find_pre(i);
                    if (pos == -1)
                        printf("Put %s first\n", book[i].name);
                    else
                        printf("Put %s after %s\n", book[i].name,
                               book[pos].name);
                    value[book[i].name] = 1;
                }
            printf("END\n");
        }
    }
    return 0;
}
