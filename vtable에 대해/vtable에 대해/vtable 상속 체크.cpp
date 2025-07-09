

int main() {
    cout << "=== 상속 시 vtable 변화 테스트 ===" << endl;
    cout << endl;

    // Base 객체 생성
    Base* baseObj = new Base();
    analyzeVtable(baseObj, "Base");

    // Derived 객체 생성
    Derived* derivedObj = new Derived();
    analyzeVtable(derivedObj, "Derived");

    // Base 포인터로 Derived 객체 가리키기
    Base* polymorphicObj = new Derived();
    analyzeVtable(polymorphicObj, "Base* -> Derived");

    cout << "=== vtable 비교 ===" << endl;
    void** baseVtable = *(void***)baseObj;
    void** derivedVtable = *(void***)derivedObj;
    void** polymorphicVtable = *(void***)polymorphicObj;

    cout << "Base vtable:          " << baseVtable << endl;
    cout << "Derived vtable:       " << derivedVtable << endl;
    cout << "Polymorphic vtable:   " << polymorphicVtable << endl;

    cout << endl;
    cout << "Base와 Derived vtable이 같은가?     " << (baseVtable == derivedVtable ? "같음" : "다름") << endl;
    cout << "Derived와 Polymorphic이 같은가?     " << (derivedVtable == polymorphicVtable ? "같음" : "다름") << endl;

    cout << endl;
    cout << "=== 함수 주소 비교 (오버라이드 vs 상속) ===" << endl;
    cout << "Base::func1 주소:       " << baseVtable[0] << endl;
    cout << "Derived::func1 주소:    " << derivedVtable[0] << " (오버라이드됨)" << endl;
    cout << "Base::func2 주소:       " << baseVtable[1] << endl;
    cout << "Derived::func2 주소:    " << derivedVtable[1] << " (상속됨)" << endl;
    cout << "Base::func3 주소:       " << baseVtable[2] << endl;
    cout << "Derived::func3 주소:    " << derivedVtable[2] << " (오버라이드됨)" << endl;

    cout << endl;
    cout << "주소 비교 결과:" << endl;
    cout << "func1 주소 같은가? " << (baseVtable[0] == derivedVtable[0] ? "같음 (상속)" : "다름 (오버라이드)") << endl;
    cout << "func2 주소 같은가? " << (baseVtable[1] == derivedVtable[1] ? "같음 (상속)" : "다름 (오버라이드)") << endl;
    cout << "func3 주소 같은가? " << (baseVtable[2] == derivedVtable[2] ? "같음 (상속)" : "다름 (오버라이드)") << endl;

    cout << endl;
    cout << "=== 다형성 테스트 ===" << endl;
    cout << "Base* 포인터로 호출:" << endl;
    polymorphicObj->func1();  // Derived::func1이 호출됨 (오버라이드)
    polymorphicObj->func2();  // Base::func2가 호출됨 (상속)
    polymorphicObj->func3();  // Derived::func3이 호출됨 (오버라이드)

    cout << "vtable 직접 호출:" << endl;
    typedef void(*FuncPtr)(Base*);
    FuncPtr f1 = (FuncPtr)polymorphicVtable[0];
    FuncPtr f2 = (FuncPtr)polymorphicVtable[1];
    FuncPtr f3 = (FuncPtr)polymorphicVtable[2];
    f1(polymorphicObj);  // Derived::func1이 호출됨
    f2(polymorphicObj);  // Base::func2가 호출됨
    f3(polymorphicObj);  // Derived::func3이 호출됨

    delete baseObj;
    delete derivedObj;
    delete polymorphicObj;

    return 0;
}