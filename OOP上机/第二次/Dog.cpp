#include <iostream>
#include <cstring>  
using namespace std;

class Dog {
public:
    char* name;
    int age;
    char sex;
    float weight;

    Dog(const char* n, int a, char s, float w) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        age = a;
        sex = s;
        weight = w;
    }

    void Show() const {
        cout << "Name: " << name << ", Age: " << age 
             << ", Sex: " << sex << ", Weight: " << weight << " kg" << endl;
    }

    ~Dog() {
        delete[] name;
    }
};

int main() {
    Dog* d1 = new Dog("Buddy", 3, 'M', 10.5);
    d1->Show();
    delete d1;

    return 0;
}

