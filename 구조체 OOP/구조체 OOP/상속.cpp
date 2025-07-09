#include <iostream>
#include <string>
using namespace std;

// �θ� ����ü
struct Animal 
{
    string name;
    int age;

    Animal(const string& n, int a) : name(n), age(a) 
    {
        cout << "Animal ������ ȣ��: " << name << endl;
    }

    void eat() 
    {
        cout << name << "��(��) �԰� �ֽ��ϴ�." << endl;
    }

    void sleep() 
    {
        cout << name << "��(��) �ڰ� �ֽ��ϴ�." << endl;
    }

    void showInfo()
    {
        cout << "�̸�: " << name << ", ����: " << age << "��" << endl;
    }
};

// �ڽ� ����ü 1
struct Dog : public Animal 
{
    string breed;

    Dog(const string& n, int a, const string& b) : Animal(n, a), breed(b) 
    {
        cout << "Dog ������ ȣ��: " << name << " (" << breed << ")" << endl;
    }

    void bark() 
    {
        cout << name << "��(��) �۸� ¢���ϴ�!" << endl;
    }

    void wagTail()
    {
        cout << name << "��(��) ������ ���ϴ�." << endl;
    }

    void showDogInfo()
    {
        showInfo();  // �θ� �޼��� ȣ��
        cout << "����: " << breed << endl;
    }
};

// �ڽ� ����ü 2
struct Cat : public Animal 
{
    bool isIndoor;

    Cat(const string& n, int a, bool indoor) : Animal(n, a), isIndoor(indoor) 
    {
        cout << "Cat ������ ȣ��: " << name << endl;
    }

    void meow() 
    {
        cout << name << "��(��) �߿� ��ϴ�!" << endl;
    }

    void purr() 
    {
        cout << name << "��(��) �׸��� �Ÿ��ϴ�." << endl;
    }

    void showCatInfo() 
    {
        showInfo();  // �θ� �޼��� ȣ��
        cout << "�ǳ��� ����: " << (isIndoor ? "��" : "�ƴϿ�") << endl;
    }
};

int main()
{
    cout << "=== ����ü ��� �׽�Ʈ ===" << endl << endl;

    // �� ��ü ����
    cout << "1. Dog ��ü ����:" << endl;
    Dog myDog("�ٵ���", 3, "������");
    cout << endl;

    // �θ� Ŭ���� �޼��� ���
    cout << "2. �θ� Ŭ���� �޼��� ȣ��:" << endl;
    myDog.eat();
    myDog.sleep();
    cout << endl;

    // �ڽ� Ŭ���� �޼��� ���
    cout << "3. �ڽ� Ŭ���� �޼��� ȣ��:" << endl;
    myDog.bark();
    myDog.wagTail();
    cout << endl;

    // ����� ��ü ����
    cout << "4. Cat ��ü ����:" << endl;
    Cat myCat("����", 2, true);
    cout << endl;

    // ����� �޼��� �׽�Ʈ
    cout << "5. Cat �޼��� ȣ��:" << endl;
    myCat.eat();     // �θ� �޼���
    myCat.meow();    // �ڽ� �޼���
    myCat.purr();    // �ڽ� �޼���
    cout << endl;

    // ���� ���
    cout << "6. ���� ���:" << endl;
    myDog.showDogInfo();
    cout << "---" << endl;
    myCat.showCatInfo();
    cout << endl;

    // �θ� Ÿ�� �����ͷ� �ڽ� ��ü ����Ű��
    cout << "7. �θ� Ÿ�� ������ �׽�Ʈ:" << endl;
    Animal* animalPtr1 = &myDog;
    Animal* animalPtr2 = &myCat;

    animalPtr1->eat();
    animalPtr1->showInfo();
    cout << "---" << endl;
    animalPtr2->eat();
    animalPtr2->showInfo();

    cout << endl << "����� ���������� �۵��մϴ�!" << endl;

    return 0;
}

//================================================//
/* ����
C++���� struct�� class�� ������ �������� �⺻ ���� �����ڻ��Դϴ� :

struct : ������� �⺻������ public
class : ������� �⺻������ private

������ ���
C++�� C���� �����ϸ鼭 ���� C �ڵ���� ȣȯ���� �����ϱ� ���� struct Ű���带 �״�� �ε�, ��ü���� ����� ��� �߰��� ���Դϴ�. ���� ����ü�� ������, �Ҹ���, ���, �����Լ� ���� ��� ����� �� �ֽ��ϴ�.
���������, ����ü ����� C++���� struct�� class�� ������ ��� ����ü�̱� ������ �ڿ������� �����Ǵ� ����Դϴ�.


 */