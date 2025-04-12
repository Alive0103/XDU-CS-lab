#include <iostream>
#include <string>
using namespace std;

// Teacher ��
class Teacher {
protected:
    string name;
    int age;
    string gender;
    string address;
    string phone;
    string title;  // ְ��
public:
    void input();  // ����������������
    void display() const;  // ����������������
};

// Cadre ��
class Cadre {
protected:
    string name;
    int age;
    string gender;
    string address;
    string phone;
    string post;  // ְ��
public:
    void input();  // ����������������
    void display() const;  // ����������������
};

// Teacher_Cadre �࣬�̳��� Teacher �� Cadre
class Teacher_Cadre : public Teacher, public Cadre {
private:
    double wages;  // ����
public:
    void input();  // ����������������
    void show() const;  // ����������������
};

// Teacher ���Ա��������
void Teacher::input() {
    cout << "����������: ";
    cin >> name;
    cout << "����������: ";
    cin >> age;
    cout << "�������Ա�: ";
    cin >> gender;
    cout << "�������ַ: ";
    cin >> address;
    cout << "������绰: ";
    cin >> phone;
    cout << "������ְ��: ";
    cin >> title;
}

void Teacher::display() const {
    cout << "����: " << name << ", ����: " << age << ", �Ա�: " << gender
         << ", ��ַ: " << address << ", �绰: " << phone << ", ְ��: " << title << endl;
}

// Cadre ���Ա��������
void Cadre::input() {
    cout << "����������: ";
    cin >> name;
    cout << "����������: ";
    cin >> age;
    cout << "�������Ա�: ";
    cin >> gender;
    cout << "�������ַ: ";
    cin >> address;
    cout << "������绰: ";
    cin >> phone;
    cout << "������ְ��: ";
    cin >> post;
}

void Cadre::display() const {
    cout << "����: " << name << ", ����: " << age << ", �Ա�: " << gender
         << ", ��ַ: " << address << ", �绰: " << phone << ", ְ��: " << post << endl;
}

// Teacher_Cadre ���Ա��������
void Teacher_Cadre::input() {
    Teacher::input();  // ���� Teacher ������뺯��
    Cadre::input();    // ���� Cadre ������뺯��
    cout << "�����빤��: ";
    cin >> wages;
}

void Teacher_Cadre::show() const {
    Teacher::display();  // ��ʾ Teacher �����Ϣ
    Cadre::display();    // ��ʾ Cadre �����Ϣ
    cout << "����: " << wages << endl;
}

int main() {
    Teacher_Cadre teacher_cadre;
    teacher_cadre.input();
    cout << "\n��ʦ��ɲ���Ϣ:" << endl;
    teacher_cadre.show();
    
    return 0;
}

