#include <iostream> 

class AbstractClass
{
public:
    virtual void pureVirtualFunc() = 0; // 순수 가상 함수
};

struct AbstractStruct 
{
    virtual void pureVirtualFunc() = 0; // 순수 가상 함수
};

class MyClass : public AbstractClass 
{
public:
    void pureVirtualFunc() override
    {
        // 구현
    }
};

struct MyStruct : public AbstractStruct 
{
    void pureVirtualFunc() override
    {
        // 구현
    }
};

int main() 
{
    // AbstractClass ac; // 컴파일 에러: 추상 클래스는 인스턴스화할 수 없음
    // AbstractStruct as; // 컴파일 에러: 추상 구조체는 인스턴스화할 수 없음
    MyClass mc;
    MyStruct ms;
    return 0;
}