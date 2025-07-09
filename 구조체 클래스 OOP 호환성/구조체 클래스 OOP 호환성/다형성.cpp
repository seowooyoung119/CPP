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
{ // 구조체가 클래스를 상속받아 가상 함수 오버라이딩
    void makeSound() override 
    {
        std::cout << "Woof woof!" << std::endl;
    }
};

class Cat : public Animal
{ // 클래스가 클래스를 상속받아 가상 함수 오버라이딩
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