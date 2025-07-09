#include <iostream> 

class Animal 
{
public:
    virtual void makeSound() 
    {
        std::cout << "Animal makes a sound" << std::endl;
    }
};

struct Dog : public Animal 
{ // ����ü�� Ŭ������ ��ӹ޾� ���� �Լ� �������̵�
    void makeSound() override 
    {
        std::cout << "Woof woof!" << std::endl;
    }
};

class Cat : public Animal
{ // Ŭ������ Ŭ������ ��ӹ޾� ���� �Լ� �������̵�
public:
    void makeSound() override
    {
        std::cout << "Meow!" << std::endl;
    }
};

int main() 
{
    Animal* myAnimal1 = new Dog();
    Animal* myAnimal2 = new Cat();
    Animal* myAnimal3 = new Animal();

    myAnimal1->makeSound(); // Woof woof!
    myAnimal2->makeSound(); // Meow!
    myAnimal3->makeSound(); // Animal makes a sound

    delete myAnimal1;
    delete myAnimal2;
    delete myAnimal3;
    return 0;
}