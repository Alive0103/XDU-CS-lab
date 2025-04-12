#include <iostream>
using namespace std;

//输入三个整数，将它们按由小到大的顺序输出，要求使用变量的引用。

/*
测试用例
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
    
    cout << "按从小到大的顺序输出：" << x << " " << y << " " << z << endl;
    
    return 0;
}
