/*
����2��3�о��������������������<<��������ȡ�������>>����
ʹ֮�����ھ��������������
*/ 

#include <iostream>
using namespace std;

class Matrix {
private:
    int mat[2][3]; // 2��3�еľ���

public:
    // �������
    friend istream& operator>>(istream& in, Matrix& m) {
        cout << "���������Ԫ�أ�2��3�У�:" << endl;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                in >> m.mat[i][j];
            }
        }
        return in;
    }

    // �������
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
    
    // �������
    cin >> m;

    // �������
    cout << "����Ϊ:" << endl;
    cout << m;

    return 0;
}

