#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// �θ� ����ü (�����Լ� ����)
struct Animal {
    string name;
    int age;

    Animal(const string& n, int a) : name(n), age(a) {}

    // �����Լ� - �������� �ٽ�
    virtual void makeSound() {
        cout << name << "��(��) �Ҹ��� ���ϴ�." << endl;
    }

    virtual void move() {
        cout << name << "��(��) �����Դϴ�." << endl;
    }

    virtual void eat() {
        cout << name << "��(��) �Խ��ϴ�." << endl;
    }

    // �Ϲ� �Լ� (�������̵� ���� ����)
    void sleep() {
        cout << name << "��(��) ���� ��ϴ�." << endl;
    }

    virtual void showInfo() {
        cout << "���� ���� - �̸�: " << name << ", ����: " << age << "��" << endl;
    }

    // ���� �Ҹ��� (������ ��� �� �ʼ�)
    virtual ~Animal() {
        cout << name << " �Ҹ��� ȣ��" << endl;
    }
};

// �ڽ� ����ü 1
struct Dog : public Animal {
    string breed;

    Dog(const string& n, int a, const string& b) : Animal(n, a), breed(b) {}

    // �����Լ� �������̵�
    void makeSound() override {
        cout << name << "��(��) �۸� ¢���ϴ�!" << endl;
    }

    void move() override {
        cout << name << "��(��) �� �߷� �پ�ٴմϴ�!" << endl;
    }

    void eat() override {
        cout << name << "��(��) ��Ḧ ��ƿ�� �Խ��ϴ�!" << endl;
    }

    void showInfo() override {
        cout << "�� ���� - �̸�: " << name << ", ����: " << age << "��, ����: " << breed << endl;
    }

    // ������ ���� �޼���
    void wagTail() {
        cout << name << "��(��) ������ ���ϴ�!" << endl;
    }

    ~Dog() {
        cout << "Dog " << name << " �Ҹ��� ȣ��" << endl;
    }
};

// �ڽ� ����ü 2
struct Cat : public Animal {
    bool isIndoor;

    Cat(const string& n, int a, bool indoor) : Animal(n, a), isIndoor(indoor) {}

    // �����Լ� �������̵�
    void makeSound() override {
        cout << name << "��(��) �߿� ��ϴ�!" << endl;
    }

    void move() override {
        cout << name << "��(��) ������ �ɾ�ٴմϴ�!" << endl;
    }

    void eat() override {
        cout << name << "��(��) ����ϰ� �Խ��ϴ�!" << endl;
    }

    void showInfo() override {
        cout << "����� ���� - �̸�: " << name << ", ����: " << age << "��, �ǳ���: "
            << (isIndoor ? "��" : "�ƴϿ�") << endl;
    }

    // ����̸��� ���� �޼���
    void purr() {
        cout << name << "��(��) �׸��� �Ÿ��ϴ�!" << endl;
    }

    ~Cat() {
        cout << "Cat " << name << " �Ҹ��� ȣ��" << endl;
    }
};

// �ڽ� ����ü 3
struct Bird : public Animal {
    bool canFly;

    Bird(const string& n, int a, bool fly) : Animal(n, a), canFly(fly) {}

    void makeSound() override {
        cout << name << "��(��) ±± ��ϴ�!" << endl;
    }

    void move() override {
        if (canFly) {
            cout << name << "��(��) �ϴ��� ���ƴٴմϴ�!" << endl;
        }
        else {
            cout << name << "��(��) �� �߷� �پ�ٴմϴ�!" << endl;
        }
    }

    void eat() override {
        cout << name << "��(��) ������ �ɾ� �Խ��ϴ�!" << endl;
    }

    void showInfo() override {
        cout << "�� ���� - �̸�: " << name << ", ����: " << age << "��, ���డ��: "
            << (canFly ? "��" : "�ƴϿ�") << endl;
    }

    ~Bird() {
        cout << "Bird " << name << " �Ҹ��� ȣ��" << endl;
    }
};

// �������� Ȱ���� �Լ���
void performAnimalActions(Animal* animal) {
    cout << "=== " << animal->name << " �ൿ �׽�Ʈ ===" << endl;
    animal->makeSound();  // �� �������� �ٸ� �Ҹ�
    animal->move();       // �� �������� �ٸ� ������
    animal->eat();        // �� �������� �ٸ� �Դ� ���
    animal->showInfo();   // �� �������� �ٸ� ����
    animal->sleep();      // ���� �޼���
    cout << endl;
}

void feedAnimals(vector<unique_ptr<Animal>>& animals) {
    cout << "=== ��� ������ �޽� �ð� ===" << endl;
    for (auto& animal : animals) {
        animal->eat();  // ���� �ٸ� ������� ����
    }
    cout << endl;
}

void makeAllSounds(vector<unique_ptr<Animal>>& animals) {
    cout << "=== ��� ������ �Ҹ� ���� ===" << endl;
    for (auto& animal : animals) {
        animal->makeSound();  // ���� �ٸ� �Ҹ�
    }
    cout << endl;
}

int main() {
    cout << "=== ����ü ������ �׽�Ʈ ===" << endl << endl;

    // 1. ���� ��ü ���� �� �׽�Ʈ
    cout << "1. ���� ��ü ������ �׽�Ʈ:" << endl;
    Dog dog("�ٵ���", 3, "������");
    Cat cat("����", 2, true);
    Bird bird("±±��", 1, true);

    // �θ� Ÿ�� �����ͷ� �ڽ� ��ü ����Ű��
    Animal* animalPtr;

    animalPtr = &dog;
    performAnimalActions(animalPtr);

    animalPtr = &cat;
    performAnimalActions(animalPtr);

    animalPtr = &bird;
    performAnimalActions(animalPtr);

    // 2. �����̳ʸ� �̿��� ������ �׽�Ʈ
    cout << "2. �����̳� ������ �׽�Ʈ:" << endl;
    vector<unique_ptr<Animal>> animals;
    animals.push_back(make_unique<Dog>("�۸���", 4, "��縮Ʈ����"));
    animals.push_back(make_unique<Cat>("�߿���", 3, false));
    animals.push_back(make_unique<Bird>("�Ķ���", 2, true));
    animals.push_back(make_unique<Dog>("�ǻ�", 1, "Ǫ��"));

    // ���� �Լ��� �ٸ� ���� ����
    feedAnimals(animals);
    makeAllSounds(animals);

    // 3. ��Ÿ�� ������ Ȯ��
    cout << "3. ��Ÿ�� ������ Ȯ��:" << endl;
    cout << "�� ������ �� ����:" << endl;
    for (auto& animal : animals) {
        animal->showInfo();  // �� Ÿ�Ժ��� �ٸ� ���� ���
    }
    cout << endl;

    // 4. �����Լ� vs �Ϲ��Լ� ��
    cout << "4. �����Լ� vs �Ϲ��Լ�:" << endl;
    Animal* testPtr = &dog;
    cout << "�����Լ� ȣ�� (������ ����):" << endl;
    testPtr->makeSound();  // Dog::makeSound() ȣ��
    testPtr->move();       // Dog::move() ȣ��

    cout << "�Ϲ��Լ� ȣ�� (������ ������):" << endl;
    testPtr->sleep();      // Animal::sleep() ȣ�� (�������̵� �ȵ�)
    cout << endl;

    cout << "�������� ���������� �۵��մϴ�!" << endl;
    cout << "- �����Լ��� ���� ��Ÿ�ӿ� ������ �޼��� ȣ��" << endl;
    cout << "- ������ �������̽��� �پ��� ���� ����" << endl;
    cout << "- �θ� Ÿ�� �����ͷ� �ڽ� ��ü ���� ����" << endl;

    return 0;
}