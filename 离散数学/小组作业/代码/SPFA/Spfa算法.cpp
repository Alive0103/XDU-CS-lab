#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int cnt,head[N],d[N],n,m,vis[N];
struct edge{
int v,nxt,w;
}a[N*2];
void addedge(int u,int v,int w){
a[++cnt].v=v;
a[cnt].w=w;
a[cnt].nxt=head[u];
head[u]=cnt;
}
void spfa(int s){
queue<int>q;
memset(d,0x3f,sizeof(d));
d[s]=0;
q.push(s);
vis[s]=1;
while(!q.empty()){
int now=q.front();
q.pop();
vis[now]=0;
for(int i=head[now];i;i=a[i].nxt){
int to=a[i].v;
if(a[i].w+d[now]<=d[to]){
d[to]=a[i].w+d[now];
if(!vis[to]){
q.push(to);
vis[to]=1;
}
}
}
}
}
int main(){
cin>>n>>m;
for(int i=1;i<=m;i++){
int x,y,w;
cin>>x>>y>>w;
addedge(x,y,w);
}
spfa(1);
for(int i=1;i<=n;i++)cout<<d[i]<<" ";
return 0;
}
