#include <iostream>
using namespace std;

//�Ե�3����ú���ģ��ʵ�֣������3�������жԱȷ����� 

/*
3
9 3 15
4
2.32 4.51 10.999 3.7
*/ 

const int N = 100010;

template <typename T>
void sort(T a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                T temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    cout << "��������";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    int a[N]; 
    float b[N];
    
    int n1, n2;
    
    cin >> n1;
    for (int i = 0; i < n1; i++) {//��������
        cin >> a[i];
    }
    
    cin >> n2;
    for (int i = 0; i < n2; i++) {//���븡����
        cin >> b[i];
    }
    
    sort(a, n1);
    sort(b, n2);
    
    return 0;
}

