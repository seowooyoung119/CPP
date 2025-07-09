#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// 부모 구조체 (가상함수 포함)
struct Animal {
    string name;
    int age;

    Animal(const string& n, int a) : name(n), age(a) {}

    // 가상함수 - 다형성의 핵심
    virtual void makeSound() {
        cout << name << "이(가) 소리를 냅니다." << endl;
    }

    virtual void move() {
        cout << name << "이(가) 움직입니다." << endl;
    }

    virtual void eat() {
        cout << name << "이(가) 먹습니다." << endl;
    }

    // 일반 함수 (오버라이딩 되지 않음)
    void sleep() {
        cout << name << "이(가) 잠을 잡니다." << endl;
    }

    virtual void showInfo() {
        cout << "동물 정보 - 이름: " << name << ", 나이: " << age << "살" << endl;
    }

    // 가상 소멸자 (다형성 사용 시 필수)
    virtual ~Animal() {
        cout << name << " 소멸자 호출" << endl;
    }
};

// 자식 구조체 1
struct Dog : public Animal {
    string breed;

    Dog(const string& n, int a, const string& b) : Animal(n, a), breed(b) {}

    // 가상함수 오버라이딩
    void makeSound() override {
        cout << name << "이(가) 멍멍 짖습니다!" << endl;
    }

    void move() override {
        cout << name << "이(가) 네 발로 뛰어다닙니다!" << endl;
    }

    void eat() override {
        cout << name << "이(가) 사료를 우걱우걱 먹습니다!" << endl;
    }

    void showInfo() override {
        cout << "개 정보 - 이름: " << name << ", 나이: " << age << "살, 견종: " << breed << endl;
    }

    // 개만의 고유 메서드
    void wagTail() {
        cout << name << "이(가) 꼬리를 흔듭니다!" << endl;
    }

    ~Dog() {
        cout << "Dog " << name << " 소멸자 호출" << endl;
    }
};

// 자식 구조체 2
struct Cat : public Animal {
    bool isIndoor;

    Cat(const string& n, int a, bool indoor) : Animal(n, a), isIndoor(indoor) {}

    // 가상함수 오버라이딩
    void makeSound() override {
        cout << name << "이(가) 야옹 웁니다!" << endl;
    }

    void move() override {
        cout << name << "이(가) 조용히 걸어다닙니다!" << endl;
    }

    void eat() override {
        cout << name << "이(가) 우아하게 먹습니다!" << endl;
    }

    void showInfo() override {
        cout << "고양이 정보 - 이름: " << name << ", 나이: " << age << "살, 실내묘: "
            << (isIndoor ? "예" : "아니오") << endl;
    }

    // 고양이만의 고유 메서드
    void purr() {
        cout << name << "이(가) 그르릉 거립니다!" << endl;
    }

    ~Cat() {
        cout << "Cat " << name << " 소멸자 호출" << endl;
    }
};

// 자식 구조체 3
struct Bird : public Animal {
    bool canFly;

    Bird(const string& n, int a, bool fly) : Animal(n, a), canFly(fly) {}

    void makeSound() override {
        cout << name << "이(가) 짹짹 웁니다!" << endl;
    }

    void move() override {
        if (canFly) {
            cout << name << "이(가) 하늘을 날아다닙니다!" << endl;
        }
        else {
            cout << name << "이(가) 두 발로 뛰어다닙니다!" << endl;
        }
    }

    void eat() override {
        cout << name << "이(가) 씨앗을 쪼아 먹습니다!" << endl;
    }

    void showInfo() override {
        cout << "새 정보 - 이름: " << name << ", 나이: " << age << "살, 비행가능: "
            << (canFly ? "예" : "아니오") << endl;
    }

    ~Bird() {
        cout << "Bird " << name << " 소멸자 호출" << endl;
    }
};

// 다형성을 활용한 함수들
void performAnimalActions(Animal* animal) {
    cout << "=== " << animal->name << " 행동 테스트 ===" << endl;
    animal->makeSound();  // 각 동물별로 다른 소리
    animal->move();       // 각 동물별로 다른 움직임
    animal->eat();        // 각 동물별로 다른 먹는 방식
    animal->showInfo();   // 각 동물별로 다른 정보
    animal->sleep();      // 공통 메서드
    cout << endl;
}

void feedAnimals(vector<unique_ptr<Animal>>& animals) {
    cout << "=== 모든 동물들 급식 시간 ===" << endl;
    for (auto& animal : animals) {
        animal->eat();  // 각각 다른 방식으로 먹음
    }
    cout << endl;
}

void makeAllSounds(vector<unique_ptr<Animal>>& animals) {
    cout << "=== 모든 동물들 소리 내기 ===" << endl;
    for (auto& animal : animals) {
        animal->makeSound();  // 각각 다른 소리
    }
    cout << endl;
}

int main() {
    cout << "=== 구조체 다형성 테스트 ===" << endl << endl;

    // 1. 개별 객체 생성 및 테스트
    cout << "1. 개별 객체 다형성 테스트:" << endl;
    Dog dog("바둑이", 3, "진돗개");
    Cat cat("나비", 2, true);
    Bird bird("짹짹이", 1, true);

    // 부모 타입 포인터로 자식 객체 가리키기
    Animal* animalPtr;

    animalPtr = &dog;
    performAnimalActions(animalPtr);

    animalPtr = &cat;
    performAnimalActions(animalPtr);

    animalPtr = &bird;
    performAnimalActions(animalPtr);

    // 2. 컨테이너를 이용한 다형성 테스트
    cout << "2. 컨테이너 다형성 테스트:" << endl;
    vector<unique_ptr<Animal>> animals;
    animals.push_back(make_unique<Dog>("멍멍이", 4, "골든리트리버"));
    animals.push_back(make_unique<Cat>("야옹이", 3, false));
    animals.push_back(make_unique<Bird>("파랑이", 2, true));
    animals.push_back(make_unique<Dog>("뽀삐", 1, "푸들"));

    // 같은 함수로 다른 동작 수행
    feedAnimals(animals);
    makeAllSounds(animals);

    // 3. 런타임 다형성 확인
    cout << "3. 런타임 다형성 확인:" << endl;
    cout << "각 동물의 상세 정보:" << endl;
    for (auto& animal : animals) {
        animal->showInfo();  // 각 타입별로 다른 정보 출력
    }
    cout << endl;

    // 4. 가상함수 vs 일반함수 비교
    cout << "4. 가상함수 vs 일반함수:" << endl;
    Animal* testPtr = &dog;
    cout << "가상함수 호출 (다형성 적용):" << endl;
    testPtr->makeSound();  // Dog::makeSound() 호출
    testPtr->move();       // Dog::move() 호출

    cout << "일반함수 호출 (다형성 미적용):" << endl;
    testPtr->sleep();      // Animal::sleep() 호출 (오버라이딩 안됨)
    cout << endl;

    cout << "다형성이 정상적으로 작동합니다!" << endl;
    cout << "- 가상함수를 통해 런타임에 적절한 메서드 호출" << endl;
    cout << "- 동일한 인터페이스로 다양한 동작 수행" << endl;
    cout << "- 부모 타입 포인터로 자식 객체 조작 가능" << endl;

    return 0;
}