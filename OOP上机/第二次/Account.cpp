#include <iostream>
using namespace std;

class Account {
private:
    int accountNumber;      // 账号
    string accountName;     // 户名
    string password;        // 密码
    double balance;         // 余额
    static double rate; // 活期年利率

public:
    Account(int accNum, string accName, string pwd, double bal) 
        : accountNumber(accNum), accountName(accName), password(pwd), balance(bal) {}

    void Deposit(double amount) {
        balance += amount;
        cout << "存入金额: " << amount << " 元, 当前余额: " << balance << " 元" << endl;
    }

    void Withdraw(double amount) {
        if (amount > balance) {
            cout << "余额不足，无法取出该金额。" << endl;
        } else {
            balance -= amount;
            cout << "取出金额: " << amount << " 元, 当前余额: " << balance << " 元" << endl;
        }
    }

    void Calculate() const {
        double interest = balance * rate;
        cout << "本年度利息: " << interest << " 元" << endl;
    }

    void ShowAccountInfo() const {
        cout << "账号: " << accountNumber 
             << ", 户名: " << accountName 
             << ", 余额: " << balance << " 元" << endl;
    }
};

double Account::rate = 0.02; 

int main() {
    Account acc1(123456, "张三", "password", 1000.0);
    acc1.ShowAccountInfo();
    acc1.Deposit(500);
    acc1.Withdraw(300);
    acc1.Calculate();

    return 0;
}

