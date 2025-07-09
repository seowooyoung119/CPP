#include <iostream> 

struct BaseStruct
{
    int s_data;
};

class DerivedClass : public BaseStruct 
{ // 클래스가 구조체 상속
public:
    int c_data;
};

class BaseClass {
public:
    int c_data;
};

struct DerivedStruct : public BaseClass 
{ // 구조체가 클래스 상속
    int s_data;
};

int main()
{
    DerivedClass dc;
    dc.s_data = 1; // BaseStruct의 멤버 접근
    DerivedStruct ds;
    ds.c_data = 2; // BaseClass의 멤버 접근
    return 0;
}