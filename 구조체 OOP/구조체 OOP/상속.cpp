#include <iostream>
#include <string>
using namespace std;

// 부모 구조체
struct Animal 
{
    string name;
    int age;

    Animal(const string& n, int a) : name(n), age(a) 
    {
        cout << "Animal 생성자 호출: " << name << endl;
    }

    void eat() 
    {
        cout << name << "이(가) 먹고 있습니다." << endl;
    }

    void sleep() 
    {
        cout << name << "이(가) 자고 있습니다." << endl;
    }

    void showInfo()
    {
        cout << "이름: " << name << ", 나이: " << age << "살" << endl;
    }
};

// 자식 구조체 1
struct Dog : public Animal 
{
    string breed;

    Dog(const string& n, int a, const string& b) : Animal(n, a), breed(b) 
    {
        cout << "Dog 생성자 호출: " << name << " (" << breed << ")" << endl;
    }

    void bark() 
    {
        cout << name << "이(가) 멍멍 짖습니다!" << endl;
    }

    void wagTail()
    {
        cout << name << "이(가) 꼬리를 흔듭니다." << endl;
    }

    void showDogInfo()
    {
        showInfo();  // 부모 메서드 호출
        cout << "견종: " << breed << endl;
    }
};

// 자식 구조체 2
struct Cat : public Animal 
{
    bool isIndoor;

    Cat(const string& n, int a, bool indoor) : Animal(n, a), isIndoor(indoor) 
    {
        cout << "Cat 생성자 호출: " << name << endl;
    }

    void meow() 
    {
        cout << name << "이(가) 야옹 웁니다!" << endl;
    }

    void purr() 
    {
        cout << name << "이(가) 그르릉 거립니다." << endl;
    }

    void showCatInfo() 
    {
        showInfo();  // 부모 메서드 호출
        cout << "실내묘 여부: " << (isIndoor ? "예" : "아니오") << endl;
    }
};

int main()
{
    cout << "=== 구조체 상속 테스트 ===" << endl << endl;

    // 개 객체 생성
    cout << "1. Dog 객체 생성:" << endl;
    Dog myDog("바둑이", 3, "진돗개");
    cout << endl;

    // 부모 클래스 메서드 사용
    cout << "2. 부모 클래스 메서드 호출:" << endl;
    myDog.eat();
    myDog.sleep();
    cout << endl;

    // 자식 클래스 메서드 사용
    cout << "3. 자식 클래스 메서드 호출:" << endl;
    myDog.bark();
    myDog.wagTail();
    cout << endl;

    // 고양이 객체 생성
    cout << "4. Cat 객체 생성:" << endl;
    Cat myCat("나비", 2, true);
    cout << endl;

    // 고양이 메서드 테스트
    cout << "5. Cat 메서드 호출:" << endl;
    myCat.eat();     // 부모 메서드
    myCat.meow();    // 자식 메서드
    myCat.purr();    // 자식 메서드
    cout << endl;

    // 정보 출력
    cout << "6. 정보 출력:" << endl;
    myDog.showDogInfo();
    cout << "---" << endl;
    myCat.showCatInfo();
    cout << endl;

    // 부모 타입 포인터로 자식 객체 가리키기
    cout << "7. 부모 타입 포인터 테스트:" << endl;
    Animal* animalPtr1 = &myDog;
    Animal* animalPtr2 = &myCat;

    animalPtr1->eat();
    animalPtr1->showInfo();
    cout << "---" << endl;
    animalPtr2->eat();
    animalPtr2->showInfo();

    cout << endl << "상속이 정상적으로 작동합니다!" << endl;

    return 0;
}

//================================================//
/* 원리
C++에서 struct와 class의 유일한 차이점은 기본 접근 제어자뿐입니다 :

struct : 멤버들이 기본적으로 public
class : 멤버들이 기본적으로 private

역사적 배경
C++이 C에서 발전하면서 기존 C 코드와의 호환성을 유지하기 위해 struct 키워드를 그대로 두되, 객체지향 기능을 모두 추가한 것입니다. 따라서 구조체도 생성자, 소멸자, 상속, 가상함수 등을 모두 사용할 수 있습니다.
결론적으로, 구조체 상속은 C++에서 struct와 class가 동일한 언어 구조체이기 때문에 자연스럽게 지원되는 기능입니다.


 */