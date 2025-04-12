/*
定义Time类和Date类，Time类为Date类的友元类，
通过Time类中的display函数引用Date类对象的私有数据，
输出年、月、日和时、分、秒。
*/

#include <iostream>
using namespace std;

class Date;  

class Time {
public:
    void display(const Date& d); // 在Time类中定义显示Date的函数
};

class Date {
private:
    int year, month, day;

public:
    Date(int y, int m, int d) : year(y), month(m), day(d) {}

    // 让Time类成为Date类的友元类
    friend class Time;
};

void Time::display(const Date& d) {
    cout << "日期: " << d.year << "年 " << d.month << "月 " << d.day << "日" << endl;
}

int main() {
    Date date(2024, 11, 14);
    Time time;

    time.display(date); // 显示Date对象的信息

    return 0;
}

 
