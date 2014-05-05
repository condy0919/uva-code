#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <vector>
#include <cstdio>

using namespace std;

struct item_t {
    char ch;
    int freq;
    item_t *left, *right;

    int len;

    item_t(char _c = 0, int _f = 0, item_t* _l = 0, item_t* _r = 0):ch(_c), freq(_f), left(_l), right(_r) { len = 0; }
};

struct cmp {
    bool operator()(item_t*& a, item_t*& b) {
        return a->freq > b->freq;
    }
};

int huffman(const string& s) {
    priority_queue<item_t*, vector<item_t*>, cmp> Q;
    queue<item_t*> q;
    int freq[256] = {0}, len[256] = {0};

    string temp = s;
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());

    if (temp.length() == 1)
        return s.length();

    for (int i = 0; i < s.length(); ++i)
        ++freq[s[i]];
    for (int i = 0; i < 256; ++i)
        if (freq[i] > 0)
            Q.push(new item_t(i, freq[i]));
    while (Q.size() > 1) {
        item_t* e1 = Q.top(); Q.pop();
        item_t* e2 = Q.top(); Q.pop();
        Q.push(new item_t(0, e1->freq + e2->freq, e1, e2));
    }
    q.push(Q.top());
    while (!q.empty()) {
        item_t* e = q.front(); q.pop();
        if (!e->left && !e->right)
            len[e->ch] = e->len;
        if (e->left) {
            e->left->len = e->len + 1;
            q.push(e->left);
        }
        if (e->right) {
            e->right->len = e->len + 1;
            q.push(e->right);
        }
    }

    int ret = 0;
    for (int i = 0; i < s.length(); ++i)
        ret += len[s[i]];
    return ret;
}

int main() {
    string line;
    while (cin >> line, line != "END") {
        int normal_len = line.length() * 8;
        int huffman_len = huffman(line);
        printf("%d %d %.1lf\n", normal_len, huffman_len, normal_len * 1.0 / huffman_len);
    }
    return 0;
}
