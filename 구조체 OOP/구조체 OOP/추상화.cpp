#include <iostream>
#include <memory> // for std::unique_ptr

// �߻� �������̽� ������ �ϴ� ����ü
struct IShape 
{
    virtual void draw() const = 0; // ���� ���� �Լ�
    virtual double area() const = 0; // ���� ���� �Լ�
    virtual ~IShape() = default; // ���� �Ҹ���
};

// IShape �������̽��� �����ϴ� ��ü���� ����ü 1
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

// IShape �������̽��� �����ϴ� ��ü���� ����ü 2
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
    std::cout << "--- �߻�ȭ�� IShape �������̽� ��� ���� ---" << std::endl;

    // �������̽� �����͸� ���� ��ü���� ��ü�� ����
    std::unique_ptr<IShape> myCircle = std::make_unique<Circle>(5.0);
    std::unique_ptr<IShape> myRectangle = std::make_unique<Rectangle>(4.0, 6.0);

    // ������ Ȱ��
    processShape(*myCircle);
    std::cout << std::endl;
    processShape(*myRectangle);
    std::cout << std::endl;

    // ���� ��ü ���� �� ��� (������ �߻�ȭ�� �������̽��� ����)
    Circle c(3.0);
    Rectangle r(2.0, 5.0);

    processShape(c);
    std::cout << std::endl;
    processShape(r);

    return 0;
}

//============================================================================================//

/*

����:
IShape ����ü : ���� ���� �Լ�(= 0)�� �����Ͽ� �������̽� ������ �մϴ�.�� ����ü ��ü�δ� ��ü�� ������ �� ������, 
�ݵ�� �Ļ� ����ü���� ��� ���� ���� �Լ��� �����ؾ� �մϴ�. virtual ~IShape() = default;�� �������� ����� �� �޸� ������ �����ϱ� ���� ���� �Ҹ����Դϴ�.

Circle �� Rectangle ����ü : IShape�� ��ӹ޾� draw()�� area() �Լ��� �����մϴ�.

processShape �Լ� : IShape Ÿ���� ������ ���ڷ� �޾�, ��ü���� Ÿ�Կ� ������� draw()�� area()�� ȣ���մϴ�.
�̴� �߻�ȭ�� �������̽��� ���� ��ü�� �ٷ�� �������� �����Դϴ�.Ŭ���̾�Ʈ�� Circle���� Rectangle���� ���� IShape�� ����� ����� �� �ֽ��ϴ�.


PIMPL(Pointer to IMPLementation) ���뱸�� �̿��� �߻�ȭ
PIMPL�� ���� ���� ������ ��� ���Ͽ��� �����, ������ �ð��� ���̸�, ���� ȣȯ���� ���̴� �� ���Ǵ� ������ �����Դϴ�.�̴� �ܺο��� ����ü ���� ������ ���� �����ϴ� ���� ���� �߻�ȭ�� �����մϴ�.

�ܺο��� ����ϴ� �������̽� ����ü (PIMPL)
struct MyData 
{
public:
    // ������
    MyData(int val, const std::string& name);

    // ���� ������ �� ���� ������ (deep copy�� ���� �ʿ�)
    MyData(const MyData& other);
    MyData& operator=(const MyData& other);

    // �̵� ������ �� ���� ������
    MyData(MyData&& other) noexcept;
    MyData& operator=(MyData&& other) noexcept;

    // �Ҹ���
    ~MyData();

    // �ܺο��� ���� ������ �޼ҵ�
    void printInfo() const;
    void setValue(int val);
    int getValue() const;

private:
    std::unique_ptr<MyDataImpl> pImpl; // ���� ������ ����Ű�� ������
};

//============================================================================================//


Ÿ�� �Ұ� (Type Erasure)�� �̿��� �߻�ȭ


Ÿ�� �ҰŴ� �پ��� Ÿ���� ��ü���� ����� �������̽��� ���� �ٷ�� ��� �߻�ȭ ����Դϴ�.
�̴� std::function�̳� std::any�� ������ ������� �۵��մϴ�. ����ü���� �̿��ϱ�� �ټ� ����������, ���������� "����ü �߻�ȭ"�� Ȯ���Ͽ� ������ �� �ֽ��ϴ�.


// Step 1: �߻����� ������ �����ϴ� ��� ���� (Concept) ����ü
// �� ����ü�� ���� ������ �ƴ�, �ʿ��� ������� �����մϴ�.
struct PrintableConcept 
{
    virtual void print() const = 0;
    virtual ~PrintableConcept() = default;
};



// Step 2: �پ��� Ÿ���� ���� �� ����ü (���� ������ ����)
template <typename T>
struct PrintableModel : public PrintableConcept 
{
    T value;

    PrintableModel(const T& val) : value(val) {}

    void print() const override
    {
        // T Ÿ�Կ� ���� �ٸ��� ����
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



// Step 3: �ܺο��� ����ϴ� Value-Type Wrapper ����ü
// �� ����ü�� ���� Ÿ�� ������ ����� PrintableConcept �����͸� ���� �����մϴ�.
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