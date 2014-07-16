#include <algorithm>
#include<stdio.h>
#include <iostream>
using namespace std;

int solve(int c, int n1, int n5, int n10);

int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        int c, n1, n5, n10;
        scanf("%d %d %d %d",&c,&n1,&n5,&n10);
        printf("%d\n",solve(c, n1, n5, n10));
    }
    return 0;
}

int solve(int c, int n1, int n5, int n10)
{
    int ret = 0;
    // 如果需求 > 单个10、5+1+1+1的话
    if (c - n5 - n10 > 0) { // 10 + 1 + 1 + 1 部分
        ret += min(c - n5 - n10, n10) * 3;
        n5 += min(c - n5 - n10, n10);
    }
    ret += min(n10, c); // 使用单个10 => 8 + 1 + 1
    c -= min(n10, c); // 减少需求
    if (c == 0) // 如果单10就可以满足需求
        return ret;
    int x = n5 - c;
    if (x >= c) { // 5 + 5 => 8 + 1 + 1 这种方式就可以解决
        return ret + 2 * c;
    } else if (x > 0) { // 有a对5+5，n5-2a对5+1+1+1，则总使用次数为2a+4(n5-2a) = 4n5 - 6a, 所以a应该尽量大。则a可取n5-c
        ret += 2*x;
        c -= x;
        n5 -= 2*x; // 5 + 5 部分
    }
    ret += 4 * n5; // 5 + 1 + 1 + 1 部分
    c -= n5;
    ret += 8 * c; // 1 1 1 1 1 1 1 1 部分
    return ret;
}
