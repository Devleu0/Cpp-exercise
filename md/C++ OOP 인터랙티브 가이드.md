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

const principlesData = { encapsulation: { title: '캡슐화 (Encapsulation)', description: '관련된 데이터(멤버 변수)와 기능(멤버 함수)을 하나의 클래스로 묶고, 외부의 직접적인 접근을 막아 데이터를 보호하는 원리입니다. 이를 \*\*정보 은닉(Information Hiding)\*\*이라고 하며, 객체의 무결성을 보장합니다.', code: \`class BankAccount { private: double balance; // 잔액은 외부에서 직접 수정 불가 public: BankAccount(double initial\_balance) { balance = initial\_balance; } void deposit(double amount) { // 입금 함수를 통해서만 if (amount > 0) balance += amount; } double getBalance() { // 조회 함수를 통해서만 return balance; } };\` }, inheritance: { title: '상속 (Inheritance)', description: '기존 클래스(부모)의 특징을 새로운 클래스(자식)가 물려받는 기능입니다. 코드의 재사용성을 극대화하며, 자식 클래스는 부모의 기능을 확장하거나 자신만의 방식으로 \*\*재정의(Overriding)\*\*할 수 있습니다.', diagram: \`<div class="flex items-center justify-center space-x-4 my-4"> <div class="diagram-box">Animal (부모)</div> <div class="diagram-arrow">⬇️</div> <div class="diagram-box">Dog (자식)</div> </div>\`, code: \`// 부모 클래스 class Animal { public: void eat() { std::cout << "음식을 먹습니다." << std::endl; } }; // Animal을 상속받는 자식 클래스 class Dog : public Animal { public: void bark() { std::cout << "멍멍!" << std::endl; } }; int main() { Dog myDog; myDog.eat(); // 부모로부터 물려받은 기능 myDog.bark(); // 자신만의 기능 }\` }, polymorphism: { title: '다형성 (Polymorphism)', description: '하나의 이름(인터페이스)이 상황에 따라 각기 다른 방식으로 동작하는 것을 의미합니다. C++에서는 \*\*가상 함수(virtual function)\*\*를 통해 구현되며, 코드의 유연성과 확장성을 크게 향상시킵니다. 부모 클래스 포인터로도 자식 객체의 재정의된 함수를 올바르게 호출할 수 있습니다.', diagram: \`<div class="text-center my-4"> <div class="diagram-box">Shape\* pShape</div> <div class="flex justify-around mt-2"> <div class="diagram-arrow">↙️</div> <div class="diagram-arrow">↘️</div> </div> <div class="flex justify-around"> <div class="diagram-box">Circle 객체</div> <div class="diagram-box">Rectangle 객체</div> </div> </div>\`, code: \`class Shape { public: virtual void draw() = 0; // 순수 가상 함수 }; class Circle : public Shape { public: void draw() override { std::cout << "원을 그립니다." << std::endl; } }; class Rectangle : public Shape { public: void draw() override { std::cout << "사각형을 그립니다." << std::endl; } }; int main() { Shape\* pShape1 = new Circle(); Shape\* pShape2 = new Rectangle(); pShape1->draw(); // Circle의 draw()가 호출됨 pShape2->draw(); // Rectangle의 draw()가 호출됨 }\` } }; function updatePrinciplesContent(topic) { const data = principlesData\[topic\]; const contentDiv = document.getElementById('principles-content'); const diagramHTML = data.diagram ? data.diagram : ''; contentDiv.innerHTML = \` <div class="tab-content active"> <div class="concept-card"> <div class="p-6"> <h3 class="text-2xl font-semibold mb-2">${data.title}</h3> <p class="text-slate-600 mb-4">${data.description}</p> ${diagramHTML} </div> <div class="code-block font-coding"><pre><code>${data.code.replace(/</g, "&lt;").replace(/>/g, "&gt;")}</code></pre></div> </div> </div> \`; } function switchView(hash) { document.querySelectorAll('.content-section').forEach(section => { section.classList.remove('active'); }); const activeSection = document.querySelector(hash); if (activeSection) { activeSection.classList.add('active'); } document.querySelectorAll('.nav-link').forEach(link => { link.classList.remove('active'); if (link.getAttribute('href') === hash) { link.classList.add('active'); } }); if (hash === '#principles') { const initialTab = document.querySelector('#principles-tabs .tab-btn.active'); updatePrinciplesContent(initialTab.dataset.target); } } document.addEventListener('DOMContentLoaded', () => { const navMenu = document.getElementById('nav-menu'); const principlesTabs = document.getElementById('principles-tabs'); const menuToggle = document.getElementById('menu-toggle'); const sidebar = document.getElementById('sidebar'); navMenu.addEventListener('click', (e) => { if (e.target.tagName === 'A') { e.preventDefault(); const hash = e.target.getAttribute('href'); history.pushState(null, null, hash); switchView(hash); if(window.innerWidth < 640) { sidebar.classList.add('-translate-x-full'); } } }); if (principlesTabs) { principlesTabs.addEventListener('click', (e) => { if (e.target.classList.contains('tab-btn')) { principlesTabs.querySelector('.active').classList.remove('active'); e.target.classList.add('active'); updatePrinciplesContent(e.target.dataset.target); } }); } menuToggle.addEventListener('click', () => { sidebar.classList.toggle('-translate-x-full'); }); window.addEventListener('popstate', () => { const hash = window.location.hash || '#classes'; switchView(hash); }); const initialHash = window.location.hash || '#classes'; switchView(initialHash); });
