#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	int a[1000],b[1000];
	int i,n,j,m;
	scanf("%d %d",&m,&n);
	for(i=0;i<m;i++){
		scanf("%d",&a[i]);
	}
	for(i=0;i<n;i++){
		scanf("%d",&b[i]);
	}
	sort(a,a+m);
	sort(b,b+n);
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			printf("{<%d,%d>}\n", a[i], b[j]);
		}
	}
	return 0;
}

