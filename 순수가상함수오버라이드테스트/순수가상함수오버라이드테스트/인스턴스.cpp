#include <iostream>
#include <memory>

// �߻� Ŭ���� ����
class Animal 
{
public:
    // ���� �����Լ���
    virtual void makeSound() const = 0;
    virtual void move() const = 0;
    virtual void eat(const std::string& food) const = 0;

    // �Ϲ� �����Լ�
    virtual void sleep() const
    {
        std::cout << "Animal is sleeping..." << std::endl;
    }

    // ���� �Ҹ���
    virtual ~Animal() = default;
};

// �ùٸ� ���� - ��� ���� �����Լ��� �������̵�
class Dog : public Animal
{
public:
    void makeSound() const override
    {
        std::cout << "Woof! Woof!" << std::endl;
    }

    void move() const override
    {
        std::cout << "Dog is running on four legs" << std::endl;
    }

    void eat(const std::string& food) const override 
    {
        std::cout << "Dog is eating " << food << std::endl;
    }
};

// �߸��� ���� 1 - �Ϻ� ���� �����Լ� �̱���
class Cat : public Animal
{
public:
    void makeSound() const override 
    {
        std::cout << "Meow!" << std::endl;
    }

    // move()�� eat() �Լ��� �������� ����
    // ������ ���� �߻�: Cat�� ������ �߻� Ŭ����
};

// �߸��� ���� 2 - ��� ���� �����Լ� �̱���
class Bird : public Animal
{
public:
    // ���� �����Լ��� �ϳ��� �������� ����
    // ������ ���� �߻�: Bird�� �߻� Ŭ����
};

// �κ������� ������ �߰� Ŭ����
class Mammal : public Animal
{
public:
    void sleep() const override 
    {
        std::cout << "Mammal is sleeping peacefully..." << std::endl;
    }

    void move() const override 
    {
        std::cout << "Mammal is moving" << std::endl;
    }

    // makeSound()�� eat()�� ������ ���� �����Լ�
    // Mammal�� �߻� Ŭ������
};

// Mammal�� ��ӹ޾� ������ ����
class Horse : public Mammal
{
public:
    void makeSound() const override 
    {
        std::cout << "Neigh!" << std::endl;
    }

    void eat(const std::string& food) const override 
    {
        std::cout << "Horse is eating " << food << std::endl;
    }
};

// �߸��� ���� 3 - Mammal�� ��ӹ޾����� �Ϻ� �̱���
class Cow : public Mammal
{
public:
    void makeSound() const override 
    {
        std::cout << "Moo!" << std::endl;
    }

    // eat() �Լ��� ���� - ������ ���� �߻�
};

int main() {
    std::cout << "=== ���� �����Լ� �������̵� �׽�Ʈ ===" << std::endl;

    // �ùٸ� ����
    std::cout << "\n1. �ùٸ� ���� (Dog):" << std::endl;
    Dog dog;
    dog.makeSound();
    dog.move();
    dog.eat("dog food");
    dog.sleep();

    std::cout << "\n2. �ùٸ� ���� (Horse):" << std::endl;
    Horse horse;
    horse.makeSound();
    horse.move();
    horse.eat("hay");
    horse.sleep();

    // ������ ���
    std::cout << "\n3. ������ ���:" << std::endl;
    std::unique_ptr<Animal> animal1 = std::make_unique<Dog>();
    std::unique_ptr<Animal> animal2 = std::make_unique<Horse>();

    animal1->makeSound();
    animal2->makeSound();

    // �Ʒ� �ڵ���� ������ ������ �߻���Ŵ:

    Animal animal;  // ����: �߻� Ŭ���� �ν��Ͻ�ȭ �Ұ�
    Cat cat;        // ����: Cat�� �߻� Ŭ���� (move, eat �̱���)
    Bird bird;      // ����: Bird�� �߻� Ŭ���� (��� ���� �����Լ� �̱���)
    Mammal mammal;  // ����: Mammal�� �߻� Ŭ���� (makeSound, eat �̱���)
     Cow cow;        // ����: Cow�� �߻� Ŭ���� (eat �̱���)

    std::cout << "\n�׽�Ʈ �Ϸ�!" << std::endl;
    return 0;
}

/*
������ �� �߻��ϴ� ���� �޽��� ����:

error: cannot declare variable 'cat' to be of abstract type 'Cat'
  Cat cat;
      ^~~
note: because the following virtual functions are pure within 'Cat':
  virtual void Animal::move() const
  virtual void Animal::eat(const std::string&) const

error: cannot declare variable 'bird' to be of abstract type 'Bird'
  Bird bird;
       ^~~~
note: because the following virtual functions are pure within 'Bird':
  virtual void Animal::makeSound() const
  virtual void Animal::move() const
  virtual void Animal::eat(const std::string&) const

error: cannot declare variable 'mammal' to be of abstract type 'Mammal'
  Mammal mammal;
         ^~~~~~
note: because the following virtual functions are pure within 'Mammal':
  virtual void Animal::makeSound() const
  virtual void Animal::eat(const std::string&) const

error: cannot declare variable 'cow' to be of abstract type 'Cow'
  Cow cow;
      ^~~
note: because the following virtual functions are pure within 'Cow':
  virtual void Animal::eat(const std::string&) const
*/