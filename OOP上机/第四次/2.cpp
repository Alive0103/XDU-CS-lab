#include <iostream>
#include <string>
using namespace std;

// Teacher 类
class Teacher {
protected:
    string name;
    int age;
    string gender;
    string address;
    string phone;
    string title;  // 职称
public:
    void input();  // 在类体内声明函数
    void display() const;  // 在类体内声明函数
};

// Cadre 类
class Cadre {
protected:
    string name;
    int age;
    string gender;
    string address;
    string phone;
    string post;  // 职务
public:
    void input();  // 在类体内声明函数
    void display() const;  // 在类体内声明函数
};

// Teacher_Cadre 类，继承自 Teacher 和 Cadre
class Teacher_Cadre : public Teacher, public Cadre {
private:
    double wages;  // 工资
public:
    void input();  // 在类体内声明函数
    void show() const;  // 在类体内声明函数
};

// Teacher 类成员函数定义
void Teacher::input() {
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入年龄: ";
    cin >> age;
    cout << "请输入性别: ";
    cin >> gender;
    cout << "请输入地址: ";
    cin >> address;
    cout << "请输入电话: ";
    cin >> phone;
    cout << "请输入职称: ";
    cin >> title;
}

void Teacher::display() const {
    cout << "姓名: " << name << ", 年龄: " << age << ", 性别: " << gender
         << ", 地址: " << address << ", 电话: " << phone << ", 职称: " << title << endl;
}

// Cadre 类成员函数定义
void Cadre::input() {
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入年龄: ";
    cin >> age;
    cout << "请输入性别: ";
    cin >> gender;
    cout << "请输入地址: ";
    cin >> address;
    cout << "请输入电话: ";
    cin >> phone;
    cout << "请输入职务: ";
    cin >> post;
}

void Cadre::display() const {
    cout << "姓名: " << name << ", 年龄: " << age << ", 性别: " << gender
         << ", 地址: " << address << ", 电话: " << phone << ", 职务: " << post << endl;
}

// Teacher_Cadre 类成员函数定义
void Teacher_Cadre::input() {
    Teacher::input();  // 调用 Teacher 类的输入函数
    Cadre::input();    // 调用 Cadre 类的输入函数
    cout << "请输入工资: ";
    cin >> wages;
}

void Teacher_Cadre::show() const {
    Teacher::display();  // 显示 Teacher 类的信息
    Cadre::display();    // 显示 Cadre 类的信息
    cout << "工资: " << wages << endl;
}

int main() {
    Teacher_Cadre teacher_cadre;
    teacher_cadre.input();
    cout << "\n教师兼干部信息:" << endl;
    teacher_cadre.show();
    
    return 0;
}

