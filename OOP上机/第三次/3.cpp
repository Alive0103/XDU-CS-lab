/*
对于2行3列矩阵，重载流插入运算符“<<”和流提取运算符“>>”，
使之能用于矩阵的输入和输出。
*/ 

#include <iostream>
using namespace std;

class Matrix {
private:
    int mat[2][3]; // 2行3列的矩阵

public:
    // 输入矩阵
    friend istream& operator>>(istream& in, Matrix& m) {
        cout << "请输入矩阵元素（2行3列）:" << endl;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                in >> m.mat[i][j];
            }
        }
        return in;
    }

    // 输出矩阵
    friend ostream& operator<<(ostream& out, const Matrix& m) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                out << m.mat[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }
};

int main() {
    Matrix m;
    
    // 输入矩阵
    cin >> m;

    // 输出矩阵
    cout << "矩阵为:" << endl;
    cout << m;

    return 0;
}

