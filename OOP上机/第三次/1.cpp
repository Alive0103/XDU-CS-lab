/*
建立一个对象数组，内放5个学生的数据（学号、成绩）
（1）用指针指向数组首元素，输出第1，3，5个学生的数据；
（2）设立一个函数max，用指向对象的指针作函数参数，
在max函数中找出5个学生中成绩最高者，并输出其学号。
*/


#include <iostream>
using namespace std;

struct Student {
    int id;       // 学号
    double score; // 成绩
};

void max(Student* students) {
    int maxIndex = 0;
    for (int i = 1; i < 5; i++) {
        if (students[i].score > students[maxIndex].score) {
            maxIndex = i;
        }
    }
    cout << "成绩最高者的学号是: " << students[maxIndex].id << endl;
}

int main() {
    Student students[5] = {
        {1001, 85.5},
        {1002, 92.0},
        {1003, 78.3},
        {1004, 88.4},
        {1005, 91.6}
    };

    Student* ptr = students;  // 指针指向学生数组的首元素

    // 输出第1、3、5个学生的数据
    cout << "第1个学生: 学号 = " << ptr->id << ", 成绩 = " << ptr->score << endl;
    cout << "第3个学生: 学号 = " << (ptr + 2)->id << ", 成绩 = " << (ptr + 2)->score << endl;
    cout << "第5个学生: 学号 = " << (ptr + 4)->id << ", 成绩 = " << (ptr + 4)->score << endl;

    // 调用max函数，输出成绩最高者的学号
    max(ptr);

    return 0;
}

