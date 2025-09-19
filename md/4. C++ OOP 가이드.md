C++ OOP 가이드
===========

[클래스와 객체](#classes) [생성자와 소멸자](#constructors) [OOP 핵심 원리](#principles)

1\. 클래스와 객체
===========

객체 지향 프로그래밍의 가장 기본이 되는 벽돌입니다. 여기서는 현실 세계의 개념을 코드로 모델링하는 방법, 즉 클래스(설계도)를 정의하고 이를 바탕으로 객체(실체)를 만드는 과정을 배웁니다.

### 클래스 정의와 객체 생성

\`Car\`라는 설계도를 만들고, \`myCar\`라는 실제 자동차를 만드는 것과 같습니다. 클래스에는 데이터(멤버 변수)와 기능(멤버 함수)이 포함됩니다.

    #include <iostream>
    #include <string>
    
    class Car {
    public:
        std::string color;
        int speed;
    
        void accelerate() { speed += 10; }
        void brake() { speed -= 10; }
    };
    
    int main() {
        Car myCar; // myCar 객체 생성
        myCar.color = "파란색";
        myCar.speed = 50;
        
        myCar.accelerate();
        std::cout << "현재 속도: " << myCar.speed << "km/h" << std::endl;
        return 0;
    }

### 접근 지정자

클래스 내부의 중요한 데이터를 보호하기 위한 보안 장치입니다. 외부 접근을 허용할 부분(\`public\`)과 숨길 부분(\`private\`)을 명확히 구분합니다.

*   **\`public\`**: 어디서든 자유롭게 접근 가능.
*   **\`private\`**: 클래스 내부에서만 접근 가능. (정보 은닉)
*   **\`protected\`**: 클래스 내부와 상속받은 자식 클래스에서 접근 가능.

2\. 생성자와 소멸자
============

객체의 생명주기를 관리하는 특별한 함수입니다. 생성자는 객체가 태어날 때 초기 설정을, 소멸자는 객체가 사라질 때 뒷정리를 담당하여 자원을 효율적으로 관리합니다.

### 생성자 (Constructor)

객체가 생성될 때 단 한 번 호출되어 멤버 변수를 초기화합니다. 매개변수를 통해 객체 생성 시 필요한 값을 전달받을 수 있습니다.

    class Person {
    private:
        std::string name;
        int age;
    public:
        // 매개변수 있는 생성자
        Person(std::string p_name, int p_age) {
            name = p_name;
            age = p_age;
            std::cout << name << " 객체 생성 완료" << std::endl;
        }
    };
    
    int main() {
        Person p1("홍길동", 30); // 객체 생성 시 생성자 자동 호출
    }

### 소멸자 (Destructor)

객체가 메모리에서 사라질 때 단 한 번 호출됩니다. 동적으로 할당한 메모리를 해제하는 등의 자원 정리 작업을 수행합니다.

    class Person {
    public:
        std::string name;
        // ... 생성자 생략 ...
        ~Person() {
            std::cout << name << " 객체 소멸 완료" << std::endl;
        }
    };
    
    int main() {
        Person p1("홍길동", 30);
        // main 함수가 끝나면 p1 객체가 사라지면서 소멸자 자동 호출
        return 0; 
    }

3\. OOP 핵심 원리
=============

객체 지향 프로그래밍을 강력하고 유연하게 만드는 세 가지 기둥입니다. 이 원리들을 통해 코드의 재사용성을 높이고, 유지보수가 쉬운 프로그램을 만들 수 있습니다.

캡슐화 상속 다형성
