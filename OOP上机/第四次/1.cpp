#include <iostream>
#include <string>
using namespace std;

// Person 类基类
class Person {
protected:
    string id;
    string name;
public:
    void input() {
        cout << "请输入编号: ";
        cin >> id;
        cout << "请输入姓名: ";
        cin >> name;
    }
    void display() const {
        cout << "编号: " << id << ", 姓名: " << name << endl;
    }
};

// Student 类继承自 Person
class Student : public Person {
private:
    string classNo;
    float grade;
public:
    void input() {
        Person::input();
        cout << "请输入班号: ";
        cin >> classNo;
        cout << "请输入成绩: ";
        cin >> grade;
    }
    void display() const {
        Person::display();
        cout << "班号: " << classNo << ", 成绩: " << grade << endl;
    }
};

// Teacher 类继承自 Person
class Teacher : public Person {
private:
    string title;
    string department;
public:
    void input() {
        Person::input();
        cout << "请输入职称: ";
        cin >> title;
        cout << "请输入部门: ";
        cin >> department;
    }
    void display() const {
        Person::display();
        cout << "职称: " << title << ", 部门: " << department << endl;
    }
};

int main() {
    Student student;
    Teacher teacher;
    
    cout << "输入学生信息:" << endl;
    student.input();
    
    cout << "输入教师信息:" << endl;
    teacher.input();
    
    cout << "\n学生信息:" << endl;
    student.display();
    
    cout << "教师信息:" << endl;
    teacher.display();

    return 0;
}

