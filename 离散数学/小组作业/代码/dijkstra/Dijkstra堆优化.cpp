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
const int MAXN = 2e5 + 5;
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
int n, m;
vector<pair<int, int>> g[MAXN];
priority_queue<pair<int, int>> q;
int dis[MAXN];
bool vis[MAXN];
void dijkstra(int s)
{
    memset(vis, 0, sizeof(vis));
    memset(dis, INF, sizeof(dis));
    dis[s] = 0;
    q.push({0, s});
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = 1;
        for (auto [y, w] : g[x])
        {
            dis[y] = min(dis[y], dis[x] + w);
            q.push({-dis[y], y});
        }
    }
}
int main()
{
    int s;
    cout << "请输入节点数量，边数，和起点\n";
    cin >> n >> m >> s;
    cout << "输入无向边\n";
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    dijkstra(s);
    for (int i = 1; i <= n; i++)
        cout << dis[i] << " ";
    return 0;
}
