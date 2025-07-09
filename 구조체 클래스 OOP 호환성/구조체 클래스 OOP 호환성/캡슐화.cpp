#include <iostream> 

class MyClass 
{
private: // 기본 접근 지정자
    int private_data;
public:
    void set_data(int val) { private_data = val; }
    int get_data() { return private_data; }
};

struct MyStruct
{
    int public_data; // 기본 접근 지정자
private:
    int private_data;
public:
    void set_data(int val) { private_data = val; }
    int get_data() { return private_data; }
};

int main() 
{
    MyClass mc;
    // mc.private_data = 10; // 컴파일 에러: private 멤버 접근 불가
    mc.set_data(10);
    int class_data = mc.get_data();

    MyStruct ms;
    ms.public_data = 20; // public 멤버는 직접 접근 가능
    // ms.private_data = 30; // 컴파일 에러: private 멤버 접근 불가
    ms.set_data(30);
    int struct_data = ms.get_data();
    return 0;
}