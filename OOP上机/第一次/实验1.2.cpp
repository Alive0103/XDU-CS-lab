#include <iostream>
using namespace std;

//�������������������ǰ���С�����˳�������Ҫ��ʹ�ñ��������á�

/*
��������
4 2 19 
*/
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void sortt(int &a, int &b, int &c) {
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
}

int main() {
    int x, y, z;
    cin >> x >> y >> z;

    sortt(x, y, z);
    
    cout << "����С�����˳�������" << x << " " << y << " " << z << endl;
    
    return 0;
}
