#include <iostream>
#include <memory> // for std::unique_ptr

// 추상 인터페이스 역할을 하는 구조체
struct IShape 
{
    virtual void draw() const = 0; // 순수 가상 함수
    virtual double area() const = 0; // 순수 가상 함수
    virtual ~IShape() = default; // 가상 소멸자
};

// IShape 인터페이스를 구현하는 구체적인 구조체 1
struct Circle : public IShape 
{
    double radius;

    Circle(double r) : radius(r) {}

    void draw() const override 
    {
        std::cout << "Drawing a Circle with radius: " << radius << std::endl;
    }

    double area() const override
    {
        return 3.14159 * radius * radius;
    }
};

// IShape 인터페이스를 구현하는 구체적인 구조체 2
struct Rectangle : public IShape 
{
    double width;
    double height;

    Rectangle(double w, double h) : width(w), height(h) {}

    void draw() const override
    {
        std::cout << "Drawing a Rectangle with width: " << width << ", height: " << height << std::endl;
    }

    double area() const override
    {
        return width * height;
    }
};

void processShape(const IShape& shape)
{
    shape.draw();
    std::cout << "Area: " << shape.area() << std::endl;
}

int main()
{
    std::cout << "--- 추상화된 IShape 인터페이스 사용 예제 ---" << std::endl;

    // 인터페이스 포인터를 통해 구체적인 객체에 접근
    std::unique_ptr<IShape> myCircle = std::make_unique<Circle>(5.0);
    std::unique_ptr<IShape> myRectangle = std::make_unique<Rectangle>(4.0, 6.0);

    // 다형성 활용
    processShape(*myCircle);
    std::cout << std::endl;
    processShape(*myRectangle);
    std::cout << std::endl;

    // 직접 객체 생성 및 사용 (여전히 추상화된 인터페이스를 따름)
    Circle c(3.0);
    Rectangle r(2.0, 5.0);

    processShape(c);
    std::cout << std::endl;
    processShape(r);

    return 0;
}

//============================================================================================//

/*

설명:
IShape 구조체 : 순수 가상 함수(= 0)를 포함하여 인터페이스 역할을 합니다.이 구조체 자체로는 객체를 생성할 수 없으며, 
반드시 파생 구조체에서 모든 순수 가상 함수를 구현해야 합니다. virtual ~IShape() = default;는 다형성을 사용할 때 메모리 누수를 방지하기 위한 가상 소멸자입니다.

Circle 및 Rectangle 구조체 : IShape를 상속받아 draw()와 area() 함수를 구현합니다.

processShape 함수 : IShape 타입의 참조를 인자로 받아, 구체적인 타입에 관계없이 draw()와 area()를 호출합니다.
이는 추상화된 인터페이스를 통해 객체를 다루는 전형적인 예시입니다.클라이언트는 Circle인지 Rectangle인지 몰라도 IShape의 기능을 사용할 수 있습니다.


PIMPL(Pointer to IMPLementation) 관용구를 이용한 추상화
PIMPL은 구현 세부 사항을 헤더 파일에서 숨기고, 컴파일 시간을 줄이며, 이진 호환성을 높이는 데 사용되는 디자인 패턴입니다.이는 외부에서 구조체 내부 구현에 직접 접근하는 것을 막아 추상화를 제공합니다.

외부에서 사용하는 인터페이스 구조체 (PIMPL)
struct MyData 
{
public:
    // 생성자
    MyData(int val, const std::string& name);

    // 복사 생성자 및 대입 연산자 (deep copy를 위해 필요)
    MyData(const MyData& other);
    MyData& operator=(const MyData& other);

    // 이동 생성자 및 대입 연산자
    MyData(MyData&& other) noexcept;
    MyData& operator=(MyData&& other) noexcept;

    // 소멸자
    ~MyData();

    // 외부에서 접근 가능한 메소드
    void printInfo() const;
    void setValue(int val);
    int getValue() const;

private:
    std::unique_ptr<MyDataImpl> pImpl; // 실제 구현을 가리키는 포인터
};

//============================================================================================//


타입 소거 (Type Erasure)를 이용한 추상화


타입 소거는 다양한 타입의 객체들을 공통된 인터페이스를 통해 다루는 고급 추상화 기법입니다.
이는 std::function이나 std::any와 유사한 방식으로 작동합니다. 구조체만을 이용하기는 다소 복잡하지만, 개념적으로 "구조체 추상화"를 확장하여 보여줄 수 있습니다.


// Step 1: 추상적인 개념을 정의하는 기반 개념 (Concept) 구조체
// 이 구조체는 실제 구현이 아닌, 필요한 연산들을 선언합니다.
struct PrintableConcept 
{
    virtual void print() const = 0;
    virtual ~PrintableConcept() = default;
};



// Step 2: 다양한 타입을 위한 모델 구조체 (모델은 개념을 구현)
template <typename T>
struct PrintableModel : public PrintableConcept 
{
    T value;

    PrintableModel(const T& val) : value(val) {}

    void print() const override
    {
        // T 타입에 따라 다르게 동작
        if constexpr (std::is_same_v<T, int>)
        {
            std::cout << "Integer: " << value << std::endl;
        } else if constexpr (std::is_same_v<T, std::string>)
        {
            std::cout << "String: \"" << value << "\"" << std::endl;
        } else 
        {
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

    void print() const 
    {
        if (pImpl) {
            pImpl->print();
        } else
        {
            std::cout << "Empty printable object." << std::endl;
        }
    }
};









*/