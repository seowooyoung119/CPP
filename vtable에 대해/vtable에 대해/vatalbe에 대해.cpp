#include <iostream>
using namespace std;

class Base {
public:
    virtual void func1() { cout << "Base::func1\n"; }
    virtual void func2() { cout << "Base::func2\n"; }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void func1() override { cout << "Derived::func1\n"; }
    void func2() override { cout << "Derived::func2\n"; }
};

int main() {
    Base* obj = new Derived();

    cout << "=== ������ �ܰ躰 �м� ===" << endl;
    cout << "obj �ּ�: " << obj << endl;
    cout << endl;

    // ���� �ڵ�
    cout << "1. ����: void** vtable = *(void***)obj;" << endl;
    void** vtable = *(void***)obj;
    cout << "   vtable �ּ�: " << vtable << endl;
    cout << "   vtable[0] (func1): " << vtable[0] << endl;
    cout << "   vtable[1] (func2): " << vtable[1] << endl;
    cout << endl;

    // ��ǥ �ϳ� ���� - void**
    cout << "2. void* vtable2 = *(void**)obj;" << endl;
    void* vtable2 = *(void**)obj;
    cout << "   vtable2 �ּ�: " << vtable2 << endl;
    cout << "   (�̰͵� vtable �ּҿ� ����)" << endl;
    cout << "   vtable[0] (func1): " << vtable[0] << endl;
    cout << "   vtable[1] (func2): " << vtable[1] << endl;
    cout << endl;

    // ��ǥ �� �� ���� - void*
    cout << "3. void vtable3 = *(void*)obj;  // ������ ����!" << endl;
    cout << "   void�� �ҿ����� Ÿ���̶� ������ �Ұ�" << endl;
    cout << "   ��� char�� �غ���:" << endl;
    char vtable3 = *(char*)obj;
    cout << "   ù ��° ����Ʈ ��: " << (int)vtable3 << endl;
    cout << endl;

    // ��ǥ ����
    cout << "4. ĳ���ø�: (void***)obj" << endl;
    void*** ptr = (void***)obj;
    cout << "   ptr �ּ�: " << ptr << endl;
    cout << "   (obj �ּҿ� ����)" << endl;
    cout << endl;

    // �߰� �׽�Ʈ: �� Ÿ�Ժ� ũ��
    cout << "=== Ÿ�Ժ� ũ�� ===" << endl;
    cout << "sizeof(void*): " << sizeof(void*) << endl;
    cout << "sizeof(void**): " << sizeof(void**) << endl;
    cout << "sizeof(void***): " << sizeof(void***) << endl;
    cout << endl;

    // ���� �Լ� ȣ�� �׽�Ʈ
    cout << "=== ���� �Լ� ȣ�� ===" << endl;
    cout << "�Ϲ� ȣ��:" << endl;
    obj->func1();

    cout << "vtable ���� ���� ȣ��:" << endl;
    typedef void(*FuncPtr)(Base*);
    FuncPtr f1 = (FuncPtr)vtable[0];
    f1(obj);

    delete obj;
    return 0;
}