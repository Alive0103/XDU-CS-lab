#include <iostream>
using namespace std;

class Account {
private:
    int accountNumber;      // �˺�
    string accountName;     // ����
    string password;        // ����
    double balance;         // ���
    static double rate; // ����������

public:
    Account(int accNum, string accName, string pwd, double bal) 
        : accountNumber(accNum), accountName(accName), password(pwd), balance(bal) {}

    void Deposit(double amount) {
        balance += amount;
        cout << "������: " << amount << " Ԫ, ��ǰ���: " << balance << " Ԫ" << endl;
    }

    void Withdraw(double amount) {
        if (amount > balance) {
            cout << "���㣬�޷�ȡ���ý�" << endl;
        } else {
            balance -= amount;
            cout << "ȡ�����: " << amount << " Ԫ, ��ǰ���: " << balance << " Ԫ" << endl;
        }
    }

    void Calculate() const {
        double interest = balance * rate;
        cout << "�������Ϣ: " << interest << " Ԫ" << endl;
    }

    void ShowAccountInfo() const {
        cout << "�˺�: " << accountNumber 
             << ", ����: " << accountName 
             << ", ���: " << balance << " Ԫ" << endl;
    }
};

double Account::rate = 0.02; 

int main() {
    Account acc1(123456, "����", "password", 1000.0);
    acc1.ShowAccountInfo();
    acc1.Deposit(500);
    acc1.Withdraw(300);
    acc1.Calculate();

    return 0;
}

