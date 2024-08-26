#include <bits/stdc++.h>
using namespace std;
#define int long long
#define gc() getchar()
#define pc(a) putchar(a)
#define INF 1000000000
#define MAXN (int)(3e3+15)
template<typename T>void read(T &k)
{
    char ch=gc();T x=0,f=1;
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=gc();}
    k=x*f;
}
template<typename T>void write(T k)
{
    if(k<0){pc('-');k=-k;}
    if(k>9)write(k/10);
    pc(k%10+'0');
}
struct Edge
{
    int u,v,w,next;
}e[MAXN<<2];
struct node
{
    int u,dis;
    bool operator<(const node &o)const
        {return dis>o.dis;}
};
int n,m,pos=1,head[MAXN];
int h[MAXN],d[MAXN],vis[MAXN],cnt[MAXN],ans;
void addEdge(int u,int v,int w)
{
    e[pos]={u,v,w,head[u]};
    head[u]=pos++;
}
bool spfa()
{
    queue<int> q;
    fill(h+1,h+1+n,INF);
    q.push(0);
    vis[0]=1;h[0]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        vis[u]=0;
        for(int i=head[u]; i; i=e[i].next)
        {
            int v=e[i].v;
            if(h[v]>h[u]+e[i].w)
            {
                h[v]=h[u]+e[i].w;
                if(!vis[v])
                {
                    q.push(v);
                    vis[v]=1;
                    if(++cnt[v]>n) // n+1½áµã
                        return 0;
                }
            }
        }
    }
    return 1;
}
void dijkstra(int st)
{
    priority_queue<node> q;
    fill(d+1,d+1+n,INF);
    memset(vis,0,sizeof(vis));
    q.push({st,0});
    d[st]=0;
    while(!q.empty())
    {
        int u=q.top().u;q.pop();
        if(vis[u])
            continue;
        vis[u]=1;
        for(int i=head[u]; i; i=e[i].next)
        {
            int v=e[i].v;
            if(d[v]>d[u]+e[i].w)
            {
                d[v]=d[u]+e[i].w;
                if(!vis[v])
                    q.push({v,d[v]});
            }
        }
    }
}
signed main()
{
    read(n);read(m);
    for(int i=1,u,v,w; i<=m; i++)
    {
        read(u);read(v);read(w);
        addEdge(u,v,w);
    }
    for(int i=1; i<=n; i++)
        addEdge(0,i,0);
    if(!spfa())return puts("-1"),0;
    for(int i=1; i<pos; i++)
        e[i].w+=h[e[i].u]-h[e[i].v];
    for(int i=1; i<=n; i++)
    {
        dijkstra(i);
        int ans=0;
        for(int j=1; j<=n; j++)
        {
            if(d[j]==INF)
                ans+=j*INF;
            else
                ans+=j*(d[j]-(h[i]-h[j]));
        }
        write(ans);pc('\n');
    }
    return 0;
}

