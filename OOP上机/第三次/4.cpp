/*
����Time���Date�࣬Time��ΪDate�����Ԫ�࣬
ͨ��Time���е�display��������Date������˽�����ݣ�
����ꡢ�¡��պ�ʱ���֡��롣
*/

#include <iostream>
using namespace std;

class Date;  

class Time {
public:
    void display(const Date& d); // ��Time���ж�����ʾDate�ĺ���
};

class Date {
private:
    int year, month, day;

public:
    Date(int y, int m, int d) : year(y), month(m), day(d) {}

    // ��Time���ΪDate�����Ԫ��
    friend class Time;
};

void Time::display(const Date& d) {
    cout << "����: " << d.year << "�� " << d.month << "�� " << d.day << "��" << endl;
}

int main() {
    Date date(2024, 11, 14);
    Time time;

    time.display(date); // ��ʾDate�������Ϣ

    return 0;
}

 
