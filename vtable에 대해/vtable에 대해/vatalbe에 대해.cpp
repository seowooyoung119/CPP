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

    cout << "=== 포인터 단계별 분석 ===" << endl;
    cout << "obj 주소: " << obj << endl;
    cout << endl;

    // 원본 코드
    cout << "1. 원본: void** vtable = *(void***)obj;" << endl;
    void** vtable = *(void***)obj;
    cout << "   vtable 주소: " << vtable << endl;
    cout << "   vtable[0] (func1): " << vtable[0] << endl;
    cout << "   vtable[1] (func2): " << vtable[1] << endl;
    cout << endl;

    // 별표 하나 제거 - void**
    cout << "2. void* vtable2 = *(void**)obj;" << endl;
    void* vtable2 = *(void**)obj;
    cout << "   vtable2 주소: " << vtable2 << endl;
    cout << "   (이것도 vtable 주소와 같음)" << endl;
    cout << "   vtable[0] (func1): " << vtable[0] << endl;
    cout << "   vtable[1] (func2): " << vtable[1] << endl;
    cout << endl;

    // 별표 두 개 제거 - void*
    cout << "3. void vtable3 = *(void*)obj;  // 컴파일 에러!" << endl;
    cout << "   void는 불완전한 타입이라 역참조 불가" << endl;
    cout << "   대신 char로 해보면:" << endl;
    char vtable3 = *(char*)obj;
    cout << "   첫 번째 바이트 값: " << (int)vtable3 << endl;
    cout << endl;

    // 별표 없음
    cout << "4. 캐스팅만: (void***)obj" << endl;
    void*** ptr = (void***)obj;
    cout << "   ptr 주소: " << ptr << endl;
    cout << "   (obj 주소와 같음)" << endl;
    cout << endl;

    // 추가 테스트: 각 타입별 크기
    cout << "=== 타입별 크기 ===" << endl;
    cout << "sizeof(void*): " << sizeof(void*) << endl;
    cout << "sizeof(void**): " << sizeof(void**) << endl;
    cout << "sizeof(void***): " << sizeof(void***) << endl;
    cout << endl;

    // 실제 함수 호출 테스트
    cout << "=== 실제 함수 호출 ===" << endl;
    cout << "일반 호출:" << endl;
    obj->func1();

    cout << "vtable 통해 직접 호출:" << endl;
    typedef void(*FuncPtr)(Base*);
    FuncPtr f1 = (FuncPtr)vtable[0];
    f1(obj);

    delete obj;
    return 0;
}