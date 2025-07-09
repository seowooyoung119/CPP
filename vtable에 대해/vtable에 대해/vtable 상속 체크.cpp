

int main() {
    cout << "=== ��� �� vtable ��ȭ �׽�Ʈ ===" << endl;
    cout << endl;

    // Base ��ü ����
    Base* baseObj = new Base();
    analyzeVtable(baseObj, "Base");

    // Derived ��ü ����
    Derived* derivedObj = new Derived();
    analyzeVtable(derivedObj, "Derived");

    // Base �����ͷ� Derived ��ü ����Ű��
    Base* polymorphicObj = new Derived();
    analyzeVtable(polymorphicObj, "Base* -> Derived");

    cout << "=== vtable �� ===" << endl;
    void** baseVtable = *(void***)baseObj;
    void** derivedVtable = *(void***)derivedObj;
    void** polymorphicVtable = *(void***)polymorphicObj;

    cout << "Base vtable:          " << baseVtable << endl;
    cout << "Derived vtable:       " << derivedVtable << endl;
    cout << "Polymorphic vtable:   " << polymorphicVtable << endl;

    cout << endl;
    cout << "Base�� Derived vtable�� ������?     " << (baseVtable == derivedVtable ? "����" : "�ٸ�") << endl;
    cout << "Derived�� Polymorphic�� ������?     " << (derivedVtable == polymorphicVtable ? "����" : "�ٸ�") << endl;

    cout << endl;
    cout << "=== �Լ� �ּ� �� (�������̵� vs ���) ===" << endl;
    cout << "Base::func1 �ּ�:       " << baseVtable[0] << endl;
    cout << "Derived::func1 �ּ�:    " << derivedVtable[0] << " (�������̵��)" << endl;
    cout << "Base::func2 �ּ�:       " << baseVtable[1] << endl;
    cout << "Derived::func2 �ּ�:    " << derivedVtable[1] << " (��ӵ�)" << endl;
    cout << "Base::func3 �ּ�:       " << baseVtable[2] << endl;
    cout << "Derived::func3 �ּ�:    " << derivedVtable[2] << " (�������̵��)" << endl;

    cout << endl;
    cout << "�ּ� �� ���:" << endl;
    cout << "func1 �ּ� ������? " << (baseVtable[0] == derivedVtable[0] ? "���� (���)" : "�ٸ� (�������̵�)") << endl;
    cout << "func2 �ּ� ������? " << (baseVtable[1] == derivedVtable[1] ? "���� (���)" : "�ٸ� (�������̵�)") << endl;
    cout << "func3 �ּ� ������? " << (baseVtable[2] == derivedVtable[2] ? "���� (���)" : "�ٸ� (�������̵�)") << endl;

    cout << endl;
    cout << "=== ������ �׽�Ʈ ===" << endl;
    cout << "Base* �����ͷ� ȣ��:" << endl;
    polymorphicObj->func1();  // Derived::func1�� ȣ��� (�������̵�)
    polymorphicObj->func2();  // Base::func2�� ȣ��� (���)
    polymorphicObj->func3();  // Derived::func3�� ȣ��� (�������̵�)

    cout << "vtable ���� ȣ��:" << endl;
    typedef void(*FuncPtr)(Base*);
    FuncPtr f1 = (FuncPtr)polymorphicVtable[0];
    FuncPtr f2 = (FuncPtr)polymorphicVtable[1];
    FuncPtr f3 = (FuncPtr)polymorphicVtable[2];
    f1(polymorphicObj);  // Derived::func1�� ȣ���
    f2(polymorphicObj);  // Base::func2�� ȣ���
    f3(polymorphicObj);  // Derived::func3�� ȣ���

    delete baseObj;
    delete derivedObj;
    delete polymorphicObj;

    return 0;
}