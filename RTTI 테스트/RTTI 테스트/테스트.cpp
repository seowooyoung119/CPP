#include <iostream>
#ifdef __cpp_rtti
#include <typeinfo>
#endif

class Base {
public:
    virtual ~Base() = default;
    virtual void print() {}
};

class Derived : public Base
{
public:
    void print() override {}
};

int main() 
{
    Base* ptr = new Derived();

    // RTTI �������� ���� ����
#ifdef __cpp_rtti
    std::cout << "RTTI enabled" << std::endl;
    std::cout << typeid(*ptr).name() << std::endl;

    Derived* d = dynamic_cast<Derived*>(ptr);
    if (d) 
    {
        std::cout << "Dynamic cast successful" << std::endl;
    }
#else
    std::cout << "RTTI disabled" << std::endl;
#endif

    delete ptr;
    return 0;
}