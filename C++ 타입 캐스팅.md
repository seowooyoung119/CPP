## C-스타일 캐스팅 (C-style Cast)
가장 기본적인 형태의 캐스팅으로, C 언어에서부터 사용되던 방식입니다. 괄호 안에 변환하려는 타입을 명시합니다.<br>
(type) expression <br>
type(expression)
 <br> <br>
예시 :  <br>
int i = 10; <br>
double d = (double)i; // int를 double로 캐스팅 <br>
char c = char(i);     // int를 char로 캐스팅 (함수 호출 스타일) <br>

## C++ 스타일 캐스팅 (C++-style Cast)
C-스타일 캐스팅의 단점을 보완하기 위해 C++11부터 도입된 명확한 캐스팅 연산자들입니다.  <br>
각 연산자는 특정 목적과 규칙을 가지고 있어 안전하고 가독성이 뛰어납니다. <br>
 <br> <br>
 
### static_cast <br>
![image](https://github.com/user-attachments/assets/0122b8da-333c-40b5-959e-6d9f487743a4)

   <br> <br>
1. 관련 없는 타입 간의 변환은 허용하지 않습니다.
3. 상속 관계에 있는 클래스간의 변환을 허용합니다. <br> <br>
업캐스팅 (Upcasting): <br>
파생 클래스 포인터/참조를 기본 클래스 포인터/참조로 변환하는 것은 항상
안전하고 명시적으로 static_cast를 사용하지 않아도 암시적으로 변환됩니다.
<br> <br>
다운캐스팅 (Downcasting): <br>
기본 클래스 포인터/참조를 파생 클래스 포인터/참조로 변환하는 것은 위험할 수 있습니다. 런타임 검사가 없으므로, 실제 객체가 변환하려는 파생 클래스 타입이 아닐 경우 정의되지 않은 동작(Undefined Behavior)을 유발할 수 있습니다.

<br> <br>

예시 : <br>
![image](https://github.com/user-attachments/assets/e7324c40-f929-4d90-a173-606950093af0)
<br>
### const_cast


![image](https://github.com/user-attachments/assets/36e8a0d1-f898-4454-9503-532773a691ee)

<br><br>
오직 const 또는 volatile 한정자를 추가하거나 제거하는 데 사용됩니다. 다른 종류의 타입 변환은 허용하지 않습니다.<br>

const 객체의 const 한정자를 제거하여 비-const 함수를 호출하거나 값을 변경하는 데 사용될 수 있지만, 원본 객체가 실제로 const로 선언된 경우 const_cast를 통해 값을 변경하면 정의되지 않은 동작을 유발할 수 있습니다.<br>

주로 C 라이브러리와 같은 레거시 코드와의 상호작용이나, const와 비-const 오버로딩 함수를 처리할 때 유용합니다.<br>
<br>
예시 : <br>
![image](https://github.com/user-attachments/assets/5e850d4b-2e2e-480e-afe8-b20ea8fc468e)
<br>

### reinterpret_cast <br>
![image](https://github.com/user-attachments/assets/e246ebe4-6714-4f3a-8400-2cba057fcbf0)

<br>
가장 강력하고 위험한 캐스팅입니다. 어떤 타입의 포인터나 참조를 전혀 다른 타입의 포인터나 참조로 "재해석"할 때 사용됩니다.<br>

주로 하드웨어 관련 프로그래밍, 저수준 비트 조작, 또는 타입이 엄격하게 지켜지지 않는 경우에 사용됩니다.<br>

컴파일러가 타입 안정성을 전혀 검사하지 않으므로, 잘못 사용하면 심각한 런타임 오류를 초래할 수 있습니다.<br>

변환된 포인터를 역참조할 경우 정의되지 않은 동작이 발생할 가능성이 매우 높습니다.<br>

![image](https://github.com/user-attachments/assets/f12a57f4-3f2d-4c5a-94ed-dd019c9551a7)

<br><br>

### dynamic_cast <br>
![image](https://github.com/user-attachments/assets/9f7930fb-7826-450e-a0f5-268c7dbce5e3)

<br>
주로 다형성을 활용하는 상속 계층 구조에서 안전한 다운캐스팅을 수행할 때 사용됩니다.<br>

반드시 하나 이상의 가상 함수를 포함하는 다형적인 클래스에서만 사용 가능합니다. (클래스에 가상 함수가 없으면 컴파일 오류 발생)<br>

런타임에 실제 객체의 타입을 검사하여 변환 가능 여부를 확인합니다.<br>

변환이 성공하면 유효한 포인터/참조를 반환합니다.<br>

포인터 캐스팅의 경우, 변환에 실패하면 nullptr를 반환합니다.<br>

참조 캐스팅의 경우, 변환에 실패하면 std::bad_cast 예외를 발생시킵니다.<br>
![image](https://github.com/user-attachments/assets/0786a655-94ce-45db-b4cc-483eb9e881ee)
![image](https://github.com/user-attachments/assets/e1c3534f-28ad-4800-9a58-ae41dbc624dc)


---

## 언제 어떤 캐스팅을 사용할까?

### static_cast:

기본 타입 간의 안전한 변환.

상속 관계에서 업캐스팅(파생 -> 기본) 또는 안전이 보장되는 다운캐스팅 (실제 객체 타입을 알고 있을 때).

void*와의 변환.

암시적 변환을 명시적으로 표현하고 싶을 때.

### const_cast:

const 또는 volatile 한정자를 추가하거나 제거할 때. (매우 주의해서 사용)

### reinterpret_cast:

저수준 프로그래밍, 주소 조작 등 매우 특수한 경우. (최대한 사용을 자제해야 함)

### dynamic_cast:

다형적인 클래스 계층에서 안전한 다운캐스팅을 수행할 때. (런타임 타입 검사 필요)

### C-스타일 캐스팅:

가급적 사용을 피하고 C++ 스타일 캐스팅을 사용하는 것이 좋습니다. C++ 스타일 캐스팅이 더 명확하고 안전합니다.













