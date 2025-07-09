#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <functional> // for std::function (optional, for type-erased operations)

// Step 1: 추상적인 개념을 정의하는 기반 개념 (Concept) 구조체
// 이 구조체는 실제 구현이 아닌, 필요한 연산들을 선언합니다.
struct PrintableConcept {
    virtual void print() const = 0;
    virtual ~PrintableConcept() = default;
};

// Step 2: 다양한 타입을 위한 모델 구조체 (모델은 개념을 구현)
template <typename T>
struct PrintableModel : public PrintableConcept {
    T value;

    PrintableModel(const T& val) : value(val) {}

    void print() const override {
        // T 타입에 따라 다르게 동작
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

// Step 3: 외부에서 사용하는 Value-Type Wrapper 구조체
// 이 구조체가 실제 타입 정보를 숨기고 PrintableConcept 포인터를 통해 접근합니다.
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
    std::cout << "--- 타입 소거를 이용한 추상화 예제 ---" << std::endl;

    std::vector<AnyPrintable> printables;
    printables.emplace_back(123);           // int
    printables.emplace_back(3.14);          // double
    printables.emplace_back(std::string("Hello Type Erasure")); // std::string
    printables.emplace_back('A');           // char

    for (const auto& p : printables) {
        p.print();
    }
    std::cout << std::endl;

    // 다른 예시
    AnyPrintable myInt = 42;
    AnyPrintable myString = std::string("Another String");

    myInt.print();
    myString.print();

    return 0;
}