/*
����һ���������飬�ڷ�5��ѧ�������ݣ�ѧ�š��ɼ���
��1����ָ��ָ��������Ԫ�أ������1��3��5��ѧ�������ݣ�
��2������һ������max����ָ������ָ��������������
��max�������ҳ�5��ѧ���гɼ�����ߣ��������ѧ�š�
*/


#include <iostream>
using namespace std;

struct Student {
    int id;       // ѧ��
    double score; // �ɼ�
};

void max(Student* students) {
    int maxIndex = 0;
    for (int i = 1; i < 5; i++) {
        if (students[i].score > students[maxIndex].score) {
            maxIndex = i;
        }
    }
    cout << "�ɼ�����ߵ�ѧ����: " << students[maxIndex].id << endl;
}

int main() {
    Student students[5] = {
        {1001, 85.5},
        {1002, 92.0},
        {1003, 78.3},
        {1004, 88.4},
        {1005, 91.6}
    };

    Student* ptr = students;  // ָ��ָ��ѧ���������Ԫ��

    // �����1��3��5��ѧ��������
    cout << "��1��ѧ��: ѧ�� = " << ptr->id << ", �ɼ� = " << ptr->score << endl;
    cout << "��3��ѧ��: ѧ�� = " << (ptr + 2)->id << ", �ɼ� = " << (ptr + 2)->score << endl;
    cout << "��5��ѧ��: ѧ�� = " << (ptr + 4)->id << ", �ɼ� = " << (ptr + 4)->score << endl;

    // ����max����������ɼ�����ߵ�ѧ��
    max(ptr);

    return 0;
}

