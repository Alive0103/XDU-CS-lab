#include <iostream>
using namespace std;

//��2����3���������е���������ô���Ĭ�ϲ����ĺ���ʵ�֡�

/*
2��������������
2
6 1

3������������
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
		cout << "��������������" << a << ' ' << b << endl; 
		m = maxx(a,b);
	}
	else{
		cin >> a >> b >> c;
		cout << "��������������" << a << ' ' << b << ' ' << c << endl; 
		m = maxx(a,b,c);
	}
	
	cout << "���ֵΪ��" << m;
	
	return 0;
}
