#include <iostream>
#include <cmath>
using namespace std;

// 抽象基类 Shape
class Shape {
public:
    virtual double area() const = 0;  // 纯虚函数
    virtual ~Shape() {}  // 虚析构函数
};

// 圆形类
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const  {
        return M_PI * radius * radius;
    }
};

// 正方形类
class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {}
    double area() const  {
        return side * side;
    }
};

// 矩形类
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const  {
        return width * height;
    }
};

// 梯形类
class Trapezoid : public Shape {
private:
    double a, b, height;
public:
    Trapezoid(double x, double y, double h) : a(x), b(y), height(h) {}
    double area() const  {
        return 0.5 * (a + b) * height;
    }
};

// 三角形类
class Triangle : public Shape {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    double area() const  {
        return 0.5 * base * height;
    }
};

int main() {
    Shape* shapes[5];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Square(4.0);
    shapes[2] = new Rectangle(6.0, 8.0);
    shapes[3] = new Trapezoid(3.0, 5.0, 4.0);
    shapes[4] = new Triangle(6.0, 4.0);
    
    double total_area = 0;
    for (int i = 0; i < 5; ++i) {
        total_area += shapes[i]->area();
    }

    cout << "所有图形的总面积是: " << total_area << endl;

    for (int i = 0; i < 5; ++i) {
        delete shapes[i];
    }

    return 0;
}

