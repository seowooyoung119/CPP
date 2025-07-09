#include <iostream>
#include <string>
using namespace std;

struct BankAccount {
private:
    // private 멤버: 외부에서 직접 접근 불가
    double balance;
    string accountNumber;
    string password;

protected:
    // protected 멤버: 자식 클래스에서만 접근 가능
    void logTransaction(const string& type, double amount) {
        cout << "[로그] " << type << ": $" << amount << " (잔액: $" << balance << ")" << endl;
    }

    bool verifyPassword(const string& inputPassword) {
        return password == inputPassword;
    }

public:
    // public 멤버: 외부에서 자유롭게 접근 가능
    BankAccount(const string& accNum, const string& pwd, double initialBalance = 0.0)
        : accountNumber(accNum), password(pwd), balance(initialBalance) {
        cout << "계좌 생성: " << accountNumber << " (초기 잔액: $" << balance << ")" << endl;
    }

    // 안전한 입금 인터페이스
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "입금 실패: 양수 금액만 입금 가능합니다." << endl;
            return;
        }
        balance += amount;
        logTransaction("입금", amount);
    }

    // 안전한 출금 인터페이스
    bool withdraw(double amount, const string& inputPassword) {
        if (!verifyPassword(inputPassword)) {
            cout << "출금 실패: 비밀번호가 틀렸습니다." << endl;
            return false;
        }

        if (amount <= 0) {
            cout << "출금 실패: 양수 금액만 출금 가능합니다." << endl;
            return false;
        }

        if (amount > balance) {
            cout << "출금 실패: 잔액이 부족합니다. (현재 잔액: $" << balance << ")" << endl;
            return false;
        }

        balance -= amount;
        logTransaction("출금", amount);
        return true;
    }

    // 잔액 조회 (읽기 전용)
    double getBalance() const {
        return balance;
    }

    // 계좌번호 조회 (읽기 전용)
    string getAccountNumber() const {
        return accountNumber;
    }

    // 계좌 정보 출력
    void showAccountInfo() const {
        cout << "계좌번호: " << accountNumber << ", 잔액: $" << balance << endl;
    }
};

// 상속을 통한 캡슐화 테스트
struct SavingsAccount : public BankAccount {
private:
    double interestRate;
    int minBalance;

public:
    SavingsAccount(const string& accNum, const string& pwd, double initialBalance,
        double rate, int minBal)
        : BankAccount(accNum, pwd, initialBalance), interestRate(rate), minBalance(minBal) {
        cout << "적금 계좌 생성 (이자율: " << (rate * 100) << "%)" << endl;
    }

    // 이자 적용 (protected 멤버 사용)
    void applyInterest() {
        double interest = getBalance() * interestRate;
        if (interest > 0) {
            // 부모의 protected 메서드 호출
            BankAccount::deposit(interest);  // private balance에 직접 접근하지 않고 public 메서드 사용
            logTransaction("이자", interest);  // protected 메서드 사용
        }
    }

    // 특별 출금 (최소 잔액 확인)
    bool specialWithdraw(double amount, const string& inputPassword) {
        if (getBalance() - amount < minBalance) {
            cout << "출금 실패: 최소 잔액($" << minBalance << ")을 유지해야 합니다." << endl;
            return false;
        }
        return withdraw(amount, inputPassword);
    }
};

int main() {
    cout << "=== 구조체 캡슐화 테스트 ===" << endl << endl;

    // 1. 일반 계좌 생성
    cout << "1. 일반 계좌 생성:" << endl;
    BankAccount account("123-456-789", "mypassword", 1000.0);
    cout << endl;

    // 2. Public 메서드를 통한 안전한 접근
    cout << "2. Public 메서드 테스트:" << endl;
    account.showAccountInfo();
    account.deposit(500.0);
    account.deposit(-100.0);  // 에러 테스트
    cout << endl;

    // 3. 출금 테스트 (비밀번호 확인)
    cout << "3. 출금 테스트:" << endl;
    account.withdraw(200.0, "wrongpassword");  // 비밀번호 틀림
    account.withdraw(200.0, "mypassword");     // 성공
    account.withdraw(2000.0, "mypassword");    // 잔액 부족
    cout << endl;

    // 4. 적금 계좌 생성 및 테스트
    cout << "4. 적금 계좌 테스트:" << endl;
    SavingsAccount savings("987-654-321", "savingspass", 2000.0, 0.05, 100);
    savings.showAccountInfo();
    cout << endl;

    // 5. 이자 적용 (protected 멤버 사용)
    cout << "5. 이자 적용 테스트:" << endl;
    savings.applyInterest();
    savings.showAccountInfo();
    cout << endl;

    // 6. 특별 출금 테스트
    cout << "6. 특별 출금 테스트:" << endl;
    savings.specialWithdraw(1950.0, "savingspass");  // 최소 잔액 위반
    savings.specialWithdraw(1000.0, "savingspass");  // 성공
    savings.showAccountInfo();
    cout << endl;

    // 7. 캡슐화 확인
    cout << "7. 캡슐화 확인:" << endl;
    cout << "계좌 번호 (공개): " << account.getAccountNumber() << endl;
    cout << "잔액 (읽기 전용): $" << account.getBalance() << endl;

    // 다음 코드들은 컴파일 에러 발생 (주석 처리)
    // account.balance = 5000.0;        // 에러: private 멤버
    // account.password = "newpass";    // 에러: private 멤버
    // account.logTransaction("test", 100);  // 에러: protected 멤버

    cout << endl << "캡슐화가 정상적으로 작동합니다!" << endl;
    cout << "- private 멤버: 외부 접근 차단" << endl;
    cout << "- protected 멤버: 자식 클래스에서만 접근 가능" << endl;
    cout << "- public 멤버: 안전한 인터페이스 제공" << endl;

    return 0;
}