#include <iostream>
#include <memory>

// 추상 클래스 정의
class Animal 
{
public:
    // 순수 가상함수들
    virtual void makeSound() const = 0;
    virtual void move() const = 0;
    virtual void eat(const std::string& food) const = 0;

    // 일반 가상함수
    virtual void sleep() const
    {
        std::cout << "Animal is sleeping..." << std::endl;
    }

    // 가상 소멸자
    virtual ~Animal() = default;
};

// 올바른 구현 - 모든 순수 가상함수를 오버라이드
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

// 잘못된 구현 1 - 일부 순수 가상함수 미구현
class Cat : public Animal
{
public:
    void makeSound() const override 
    {
        std::cout << "Meow!" << std::endl;
    }

    // move()와 eat() 함수를 구현하지 않음
    // 컴파일 에러 발생: Cat은 여전히 추상 클래스
};

// 잘못된 구현 2 - 모든 순수 가상함수 미구현
class Bird : public Animal
{
public:
    // 순수 가상함수를 하나도 구현하지 않음
    // 컴파일 에러 발생: Bird는 추상 클래스
};

// 부분적으로 구현된 중간 클래스
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

    // makeSound()와 eat()는 여전히 순수 가상함수
    // Mammal도 추상 클래스임
};

// Mammal을 상속받아 완전히 구현
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

// 잘못된 구현 3 - Mammal을 상속받았지만 일부 미구현
class Cow : public Mammal
{
public:
    void makeSound() const override 
    {
        std::cout << "Moo!" << std::endl;
    }

    // eat() 함수가 없음 - 컴파일 에러 발생
};

int main() {
    std::cout << "=== 순수 가상함수 오버라이드 테스트 ===" << std::endl;

    // 올바른 사용법
    std::cout << "\n1. 올바른 구현 (Dog):" << std::endl;
    Dog dog;
    dog.makeSound();
    dog.move();
    dog.eat("dog food");
    dog.sleep();

    std::cout << "\n2. 올바른 구현 (Horse):" << std::endl;
    Horse horse;
    horse.makeSound();
    horse.move();
    horse.eat("hay");
    horse.sleep();

    // 다형성 사용
    std::cout << "\n3. 다형성 사용:" << std::endl;
    std::unique_ptr<Animal> animal1 = std::make_unique<Dog>();
    std::unique_ptr<Animal> animal2 = std::make_unique<Horse>();

    animal1->makeSound();
    animal2->makeSound();

    // 아래 코드들은 컴파일 에러를 발생시킴:

    Animal animal;  // 에러: 추상 클래스 인스턴스화 불가
    Cat cat;        // 에러: Cat은 추상 클래스 (move, eat 미구현)
    Bird bird;      // 에러: Bird는 추상 클래스 (모든 순수 가상함수 미구현)
    Mammal mammal;  // 에러: Mammal은 추상 클래스 (makeSound, eat 미구현)
     Cow cow;        // 에러: Cow는 추상 클래스 (eat 미구현)

    std::cout << "\n테스트 완료!" << std::endl;
    return 0;
}

/*
컴파일 시 발생하는 에러 메시지 예시:

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