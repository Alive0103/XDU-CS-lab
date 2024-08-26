#include<bits/stdc++.h>
const int maxd = 1e9;
using namespace std;
int main(){
  int s[100] , e[100] , t[100] , d[100] , n , m ;
cin>>n>>m;
  int i,j; 
  for(i = 1 ; i <= m ; i ++)
cin>>s[i] >>e[i] >>t[i];
  for( i = 1 ; i <= n ; i ++)d[i] = maxd;
  d[1] = 0;
  while(1){
   bool upd=false;
     for( j = 1 ; j <= m ; j ++){
        if(d[e[j]] > d[s[j]] + t[j]){
        d[e[j]] = d[s[j]] + t[j];
      upd=true;
         }
     }
    if(upd==false) break;
}
   for( i = 1 ; i <= n ; i ++) cout<<d[i]<<" ";
   return 0 ;
}
