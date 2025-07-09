#include <iostream> 

class AbstractClass
{
public:
    virtual void pureVirtualFunc() = 0; // ���� ���� �Լ�
};

struct AbstractStruct 
{
    virtual void pureVirtualFunc() = 0; // ���� ���� �Լ�
};

class MyClass : public AbstractClass 
{
public:
    void pureVirtualFunc() override
    {
        // ����
    }
};

struct MyStruct : public AbstractStruct 
{
    void pureVirtualFunc() override
    {
        // ����
    }
};

int main() 
{
    // AbstractClass ac; // ������ ����: �߻� Ŭ������ �ν��Ͻ�ȭ�� �� ����
    // AbstractStruct as; // ������ ����: �߻� ����ü�� �ν��Ͻ�ȭ�� �� ����
    MyClass mc;
    MyStruct ms;
    return 0;
}