#include <iostream> 

class MyClass 
{
private: // �⺻ ���� ������
    int private_data;
public:
    void set_data(int val) { private_data = val; }
    int get_data() { return private_data; }
};

struct MyStruct
{
    int public_data; // �⺻ ���� ������
private:
    int private_data;
public:
    void set_data(int val) { private_data = val; }
    int get_data() { return private_data; }
};

int main() 
{
    MyClass mc;
    // mc.private_data = 10; // ������ ����: private ��� ���� �Ұ�
    mc.set_data(10);
    int class_data = mc.get_data();

    MyStruct ms;
    ms.public_data = 20; // public ����� ���� ���� ����
    // ms.private_data = 30; // ������ ����: private ��� ���� �Ұ�
    ms.set_data(30);
    int struct_data = ms.get_data();
    return 0;
}