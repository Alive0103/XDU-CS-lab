/*
定义一个复数类Complex，
重载运算符“+”，“-”，“*”，“/”,
使之能用于复数的加、减、乘、除。
运算符重载函数作为Complex类的成员函数。
编程序，分别求两个复数之和、差、积和商。
*/ 

#include <iostream>
#include <math.h> 
using namespace std;


class Complex {
private:
    double real; // 实部
    double imag; // 虚部

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // 重载加法运算符
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    // 重载减法运算符
    Complex operator-(const Complex& other) {
        return Complex(real - other.real, imag - other.imag);
    }

    // 重载乘法运算符
    Complex operator*(const Complex& other) {
        return Complex(real * other.real - imag * other.imag, 
                       real * other.imag + imag * other.real);
    }

    // 重载除法运算符
    Complex operator/(const Complex& other) {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
                       (imag * other.real - real * other.imag) / denominator);
    }

    // 输出复数
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

