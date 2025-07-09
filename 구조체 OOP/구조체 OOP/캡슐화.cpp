#include <iostream>
#include <string>
using namespace std;

struct BankAccount {
private:
    // private ���: �ܺο��� ���� ���� �Ұ�
    double balance;
    string accountNumber;
    string password;

protected:
    // protected ���: �ڽ� Ŭ���������� ���� ����
    void logTransaction(const string& type, double amount) {
        cout << "[�α�] " << type << ": $" << amount << " (�ܾ�: $" << balance << ")" << endl;
    }

    bool verifyPassword(const string& inputPassword) {
        return password == inputPassword;
    }

public:
    // public ���: �ܺο��� �����Ӱ� ���� ����
    BankAccount(const string& accNum, const string& pwd, double initialBalance = 0.0)
        : accountNumber(accNum), password(pwd), balance(initialBalance) {
        cout << "���� ����: " << accountNumber << " (�ʱ� �ܾ�: $" << balance << ")" << endl;
    }

    // ������ �Ա� �������̽�
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "�Ա� ����: ��� �ݾ׸� �Ա� �����մϴ�." << endl;
            return;
        }
        balance += amount;
        logTransaction("�Ա�", amount);
    }

    // ������ ��� �������̽�
    bool withdraw(double amount, const string& inputPassword) {
        if (!verifyPassword(inputPassword)) {
            cout << "��� ����: ��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
            return false;
        }

        if (amount <= 0) {
            cout << "��� ����: ��� �ݾ׸� ��� �����մϴ�." << endl;
            return false;
        }

        if (amount > balance) {
            cout << "��� ����: �ܾ��� �����մϴ�. (���� �ܾ�: $" << balance << ")" << endl;
            return false;
        }

        balance -= amount;
        logTransaction("���", amount);
        return true;
    }

    // �ܾ� ��ȸ (�б� ����)
    double getBalance() const {
        return balance;
    }

    // ���¹�ȣ ��ȸ (�б� ����)
    string getAccountNumber() const {
        return accountNumber;
    }

    // ���� ���� ���
    void showAccountInfo() const {
        cout << "���¹�ȣ: " << accountNumber << ", �ܾ�: $" << balance << endl;
    }
};

// ����� ���� ĸ��ȭ �׽�Ʈ
struct SavingsAccount : public BankAccount {
private:
    double interestRate;
    int minBalance;

public:
    SavingsAccount(const string& accNum, const string& pwd, double initialBalance,
        double rate, int minBal)
        : BankAccount(accNum, pwd, initialBalance), interestRate(rate), minBalance(minBal) {
        cout << "���� ���� ���� (������: " << (rate * 100) << "%)" << endl;
    }

    // ���� ���� (protected ��� ���)
    void applyInterest() {
        double interest = getBalance() * interestRate;
        if (interest > 0) {
            // �θ��� protected �޼��� ȣ��
            BankAccount::deposit(interest);  // private balance�� ���� �������� �ʰ� public �޼��� ���
            logTransaction("����", interest);  // protected �޼��� ���
        }
    }

    // Ư�� ��� (�ּ� �ܾ� Ȯ��)
    bool specialWithdraw(double amount, const string& inputPassword) {
        if (getBalance() - amount < minBalance) {
            cout << "��� ����: �ּ� �ܾ�($" << minBalance << ")�� �����ؾ� �մϴ�." << endl;
            return false;
        }
        return withdraw(amount, inputPassword);
    }
};

int main() {
    cout << "=== ����ü ĸ��ȭ �׽�Ʈ ===" << endl << endl;

    // 1. �Ϲ� ���� ����
    cout << "1. �Ϲ� ���� ����:" << endl;
    BankAccount account("123-456-789", "mypassword", 1000.0);
    cout << endl;

    // 2. Public �޼��带 ���� ������ ����
    cout << "2. Public �޼��� �׽�Ʈ:" << endl;
    account.showAccountInfo();
    account.deposit(500.0);
    account.deposit(-100.0);  // ���� �׽�Ʈ
    cout << endl;

    // 3. ��� �׽�Ʈ (��й�ȣ Ȯ��)
    cout << "3. ��� �׽�Ʈ:" << endl;
    account.withdraw(200.0, "wrongpassword");  // ��й�ȣ Ʋ��
    account.withdraw(200.0, "mypassword");     // ����
    account.withdraw(2000.0, "mypassword");    // �ܾ� ����
    cout << endl;

    // 4. ���� ���� ���� �� �׽�Ʈ
    cout << "4. ���� ���� �׽�Ʈ:" << endl;
    SavingsAccount savings("987-654-321", "savingspass", 2000.0, 0.05, 100);
    savings.showAccountInfo();
    cout << endl;

    // 5. ���� ���� (protected ��� ���)
    cout << "5. ���� ���� �׽�Ʈ:" << endl;
    savings.applyInterest();
    savings.showAccountInfo();
    cout << endl;

    // 6. Ư�� ��� �׽�Ʈ
    cout << "6. Ư�� ��� �׽�Ʈ:" << endl;
    savings.specialWithdraw(1950.0, "savingspass");  // �ּ� �ܾ� ����
    savings.specialWithdraw(1000.0, "savingspass");  // ����
    savings.showAccountInfo();
    cout << endl;

    // 7. ĸ��ȭ Ȯ��
    cout << "7. ĸ��ȭ Ȯ��:" << endl;
    cout << "���� ��ȣ (����): " << account.getAccountNumber() << endl;
    cout << "�ܾ� (�б� ����): $" << account.getBalance() << endl;

    // ���� �ڵ���� ������ ���� �߻� (�ּ� ó��)
    // account.balance = 5000.0;        // ����: private ���
    // account.password = "newpass";    // ����: private ���
    // account.logTransaction("test", 100);  // ����: protected ���

    cout << endl << "ĸ��ȭ�� ���������� �۵��մϴ�!" << endl;
    cout << "- private ���: �ܺ� ���� ����" << endl;
    cout << "- protected ���: �ڽ� Ŭ���������� ���� ����" << endl;
    cout << "- public ���: ������ �������̽� ����" << endl;

    return 0;
}