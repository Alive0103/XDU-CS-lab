#include <iostream>
using namespace std;

//对第3题改用函数模板实现，并与第3题程序进行对比分析。 

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
    cout << "排序结果：";
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
    for (int i = 0; i < n1; i++) {//输入整数
        cin >> a[i];
    }
    
    cin >> n2;
    for (int i = 0; i < n2; i++) {//输入浮点数
        cin >> b[i];
    }
    
    sort(a, n1);
    sort(b, n2);
    
    return 0;
}

