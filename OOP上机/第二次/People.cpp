#include <iostream>
using namespace std;

class People {
protected:
    int age;
    int height;
    int weight;
    static int num; 

public:
    People(int a, int h, int w) : age(a), height(h), weight(w) {
        num++;
    }

    void Eating() {
        weight += 1;
    }

    void Sporting() {
        height += 1;
    }

    void Sleeping() {
        age += 1;
        height += 1;
        weight += 1;
    }

    void Show() const {
        cout << "Age: " << age << " years, Height: " << height << " cm, Weight: " << weight << " kg" << endl;
    }

    static void ShowNum() {
        cout << "Number of people: " << num << endl;
    }

    ~People() {
        num--;
    }
};

int People::num = 0; 

int main() {
    People p1(25, 170, 60);
    p1.Show();
    p1.Eating();
    p1.Show();
    People::ShowNum();

    People p2(30, 180, 70);
    p2.Show();
    People::ShowNum();

    return 0;
}

