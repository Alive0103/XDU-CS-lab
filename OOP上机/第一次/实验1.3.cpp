#include <iostream>
using namespace std;

//��дһ��������ͬһ���������Լ������ݽ��д�С���������������Ϳ��������͡������͡������غ���ʵ�֡�

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
	for(int i = 0;i < n1;i++){//�������� 
		cin >> a[i];
	}
	cin >> n2;
	for(int i = 0;i < n2;i++){//���븡���� 
		cin >> b[i];
	}
	sort(a, n1);
    sort(b, n2);
	return 0;
}

// ������������
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
    cout << "������������";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

// ��������������
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
    cout << "��������������";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

