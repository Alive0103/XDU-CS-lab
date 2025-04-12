#include <iostream>
using namespace std;

//编写一个程序，用同一个函数名对几个数据进行从小到大排序，数据类型可以是整型、浮点型。用重载函数实现。

/*
3
9 3 15
4
2.32 4.51 10.999 3.7
*/ 

const int N = 100010;
int main( )
{
	void sort(int a[], int n);
	void sort(float a[], int n); 
	int a[N]; 
	float b[N];
	
	int n1,n2;
	cin >> n1;
	for(int i = 0;i < n1;i++){//输入整数 
		cin >> a[i];
	}
	cin >> n2;
	for(int i = 0;i < n2;i++){//输入浮点数 
		cin >> b[i];
	}
	sort(a, n1);
    sort(b, n2);
	return 0;
}

// 整型数组排序
void sort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    cout << "整型排序结果：";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

// 浮点型数组排序
void sort(float a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                float temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    cout << "浮点型排序结果：";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

