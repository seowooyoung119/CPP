#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <functional> // for std::function (optional, for type-erased operations)

// Step 1: �߻����� ������ �����ϴ� ��� ���� (Concept) ����ü
// �� ����ü�� ���� ������ �ƴ�, �ʿ��� ������� �����մϴ�.
struct PrintableConcept {
    virtual void print() const = 0;
    virtual ~PrintableConcept() = default;
};

// Step 2: �پ��� Ÿ���� ���� �� ����ü (���� ������ ����)
template <typename T>
struct PrintableModel : public PrintableConcept {
    T value;

    PrintableModel(const T& val) : value(val) {}

    void print() const override {
        // T Ÿ�Կ� ���� �ٸ��� ����
        if constexpr (std::is_same_v<T, int>) {
            std::cout << "Integer: " << value << std::endl;
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "String: \"" << value << "\"" << std::endl;
        }
        else {
            std::cout << "Generic: " << value << std::endl;
        }
    }
};

// Step 3: �ܺο��� ����ϴ� Value-Type Wrapper ����ü
// �� ����ü�� ���� Ÿ�� ������ ����� PrintableConcept �����͸� ���� �����մϴ�.
struct AnyPrintable {
    std::unique_ptr<PrintableConcept> pImpl;

    template <typename T>
    AnyPrintable(const T& value) : pImpl(std::make_unique<PrintableModel<T>>(value)) {}

    void print() const {
        if (pImpl) {
            pImpl->print();
        }
        else {
            std::cout << "Empty printable object." << std::endl;
        }
    }
};


int main() {
    std::cout << "--- Ÿ�� �ҰŸ� �̿��� �߻�ȭ ���� ---" << std::endl;

    std::vector<AnyPrintable> printables;
    printables.emplace_back(123);           // int
    printables.emplace_back(3.14);          // double
    printables.emplace_back(std::string("Hello Type Erasure")); // std::string
    printables.emplace_back('A');           // char

    for (const auto& p : printables) {
        p.print();
    }
    std::cout << std::endl;

    // �ٸ� ����
    AnyPrintable myInt = 42;
    AnyPrintable myString = std::string("Another String");

    myInt.print();
    myString.print();

    return 0;
}