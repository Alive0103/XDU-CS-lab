#include <iostream>
#include <string>
using namespace std;

// Person �����
class Person {
protected:
    string id;
    string name;
public:
    void input() {
        cout << "��������: ";
        cin >> id;
        cout << "����������: ";
        cin >> name;
    }
    void display() const {
        cout << "���: " << id << ", ����: " << name << endl;
    }
};

// Student ��̳��� Person
class Student : public Person {
private:
    string classNo;
    float grade;
public:
    void input() {
        Person::input();
        cout << "��������: ";
        cin >> classNo;
        cout << "������ɼ�: ";
        cin >> grade;
    }
    void display() const {
        Person::display();
        cout << "���: " << classNo << ", �ɼ�: " << grade << endl;
    }
};

// Teacher ��̳��� Person
class Teacher : public Person {
private:
    string title;
    string department;
public:
    void input() {
        Person::input();
        cout << "������ְ��: ";
        cin >> title;
        cout << "�����벿��: ";
        cin >> department;
    }
    void display() const {
        Person::display();
        cout << "ְ��: " << title << ", ����: " << department << endl;
    }
};

int main() {
    Student student;
    Teacher teacher;
    
    cout << "����ѧ����Ϣ:" << endl;
    student.input();
    
    cout << "�����ʦ��Ϣ:" << endl;
    teacher.input();
    
    cout << "\nѧ����Ϣ:" << endl;
    student.display();
    
    cout << "��ʦ��Ϣ:" << endl;
    teacher.display();

    return 0;
}

