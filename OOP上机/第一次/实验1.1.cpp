#include <iostream>
using namespace std;

//求2个或3个正整数中的最大数，用带有默认参数的函数实现。

/*
2个数测试样例：
2
6 1

3个数测试样例
3
0 9 2 
*/
int maxx(int a = 3,int b = 4,int c = 7){
	int max=0;
	if(a > b && a > c) max = a;
	else if(b > c && b > a) max = b;
	else if(c > b && c > a) max = c;
	return max;
}

int main()
{
	int a,b,c,n,m;
	cin >> n;
	if(n == 2){
		cin >> a >> b;
		cout << "输入两个整数：" << a << ' ' << b << endl; 
		m = maxx(a,b);
	}
	else{
		cin >> a >> b >> c;
		cout << "输入三个整数：" << a << ' ' << b << ' ' << c << endl; 
		m = maxx(a,b,c);
	}
	
	cout << "最大值为：" << m;
	
	return 0;
}
