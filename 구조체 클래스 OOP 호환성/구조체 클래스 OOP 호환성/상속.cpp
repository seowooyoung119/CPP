#include <iostream> 

struct BaseStruct
{
    int s_data;
};

class DerivedClass : public BaseStruct 
{ // Ŭ������ ����ü ���
public:
    int c_data;
};

class BaseClass {
public:
    int c_data;
};

struct DerivedStruct : public BaseClass 
{ // ����ü�� Ŭ���� ���
    int s_data;
};

int main()
{
    DerivedClass dc;
    dc.s_data = 1; // BaseStruct�� ��� ����
    DerivedStruct ds;
    ds.c_data = 2; // BaseClass�� ��� ����
    return 0;
}