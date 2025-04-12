/*
����һ��������Complex��
�����������+������-������*������/��,
ʹ֮�����ڸ����ļӡ������ˡ�����
��������غ�����ΪComplex��ĳ�Ա������
����򣬷ֱ�����������֮�͡�������̡�
*/ 

#include <iostream>
#include <math.h> 
using namespace std;


class Complex {
private:
    double real; // ʵ��
    double imag; // �鲿

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // ���ؼӷ������
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    // ���ؼ��������
    Complex operator-(const Complex& other) {
        return Complex(real - other.real, imag - other.imag);
    }

    // ���س˷������
    Complex operator*(const Complex& other) {
        return Complex(real * other.real - imag * other.imag, 
                       real * other.imag + imag * other.real);
    }

    // ���س��������
    Complex operator/(const Complex& other) {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
                       (imag * other.real - real * other.imag) / denominator);
    }

    // �������
    void display() {
        cout << real << (imag >= 0 ? " + " : " - ") << abs(imag) << "i" << endl;
    }
};

int main() {
    Complex c1(4, 5), c2(1, -2);

    Complex sum = c1 + c2;
    Complex diff = c1 - c2;
    Complex prod = c1 * c2;
    Complex quot = c1 / c2;

    cout << "c1 + c2 = "; sum.display();
    cout << "c1 - c2 = "; diff.display();
    cout << "c1 * c2 = "; prod.display();
    cout << "c1 / c2 = "; quot.display();

    return 0;
}

