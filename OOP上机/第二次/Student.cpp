#include <iostream>
#include <cstring>
using namespace std;

class Student {
private:
    char name[18];
    int num;
    int mathScore;
    int englishScore;
    static int count;
    static int mathTotalScore;
    static int englishTotalScore;

public:
    Student(const char* nm, int nu, int math, int english) {
        strncpy(name, nm, 18);
        num = nu;
        mathScore = math;
        englishScore = english;
        count++;
        mathTotalScore += math;
        englishTotalScore += english;
    }

    void ShowBase() const {
        cout << "Name: " << name << ", ID: " << num 
             << ", Math Score: " << mathScore 
             << ", English Score: " << englishScore << endl;
    }

    static void showStatic() {
        cout << "Total Students: " << count 
             << ", Total Math Score: " << mathTotalScore 
             << ", Total English Score: " << englishTotalScore << endl;
    }

    ~Student() {
        count--;
        mathTotalScore -= mathScore;
        englishTotalScore -= englishScore;
    }
};

int Student::count = 0; 
int Student::mathTotalScore = 0;
int Student::englishTotalScore = 0;

int main() {
    Student s1("Alice", 1001, 90, 85);
    Student s2("Bob", 1002, 80, 88);

    s1.ShowBase();
    s2.ShowBase();
    Student::showStatic();

    return 0;
}

