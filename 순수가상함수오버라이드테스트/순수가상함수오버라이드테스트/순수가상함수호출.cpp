#include <iostream>
#include <cstdlib>

class Base 
{
public:
    Base()
    {
        std::cout << "Base 생성자 시작" << std::endl;
        // 함수 포인터를 통한 간접 호출로 컴파일러 속이기
        void (Base:: * ptr)() = &Base::pureFunction;
        (this->*ptr)();  // 🔥 런타임 에러!
        std::cout << "Base 생성자 완료 (실행되지 않음)" << std::endl;
    }

    virtual ~Base() 
    {
        std::cout << "Base 소멸자" << std::endl;
    }

    virtual void pureFunction() = 0;
};

class Derived : public Base 
{
public:
    Derived() 
    {
        std::cout << "Derived 생성자 (실행되지 않음)" << std::endl;
    }

    void pureFunction() override
    {
        std::cout << "Derived::pureFunction() 호출" << std::endl;
    }
};

int main() 
{
    std::cout << "객체 생성 시도..." << std::endl;

    // 다른 컴파일러/환경에서 테스트해보세요:
    // - MinGW-w64 with GCC
    // - Clang 
    // - 온라인 컴파일러들 (ideone, godbolt, etc.)

    try 
    {
        Derived d;  // 🔥 여기서 런타임 에러!
    }
    catch (...) 
    {
        std::cout << "예외 발생했지만 보통 catch되지 않음" << std::endl;
    }

    std::cout << "프로그램 정상 종료 (실행되지 않음)" << std::endl;
    return 0;
}