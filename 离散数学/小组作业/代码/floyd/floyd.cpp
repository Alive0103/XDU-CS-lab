#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define IOS cin.tie(0)->sync_with_stdio(false)
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN = 1e3 + 5;
const int INF = 0x3f3f3f3f;
int read()
{
    int X = 0, f = 1;
    char c = getchar();
    while (!isdigit(c) && c != '-')
        c = getchar();
    if (c == '-')
        c = getchar(), f = -1;
    while (isdigit(c))
        X = X * 10 + (c ^ 48), c = getchar();
    return X * f;
}
int f[MAXN][MAXN]; // f[i][j]代表节点i到节点j的最短路
int main()
{
    int n, m; //n为图中点的数量，m为图中边的数量
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            f[i][j] = 1e9; //初始每个节点对之间都是不可达，设为最大值
        }
    }
    for (int i = 1; i <= n; i++)
        f[i][i] = 0; // 自己到自己最短路为0
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;    // 分别是起点，终点和边权
        f[x][y] = f[y][x] = w; // 如果图为无向图
    }
    for (int k = 1; k <= n; k++) // 枚举转移节点
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
                // 枚举k作为i>j的转移节点计算
            }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d ", f[i][j]);
            // 输出i到j的最短路
        }
        puts("");
    }
    return 0;
}
