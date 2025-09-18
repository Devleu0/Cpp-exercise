  C++ 핵심 개념 대시보드 @import url('https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&family=Nanum+Gothic+Coding&display=swap'); body { font-family: 'Inter', sans-serif; background-color: #f1f5f9; /\* slate-100 \*/ } .font-coding { font-family: 'Nanum Gothic Coding', monospace; } .nav-link { transition: all 0.2s ease-in-out; } .nav-link.active { background-color: #e0f2fe; /\* sky-100 \*/ color: #0c4a6e; /\* sky-900 \*/ font-weight: 600; } .nav-link:hover:not(.active) { background-color: #f0f9ff; /\* sky-50 \*/ } .content-section { display: none; } .content-section.active { display: block; animation: fadeIn 0.5s ease-in-out; } @keyframes fadeIn { from { opacity: 0; transform: translateY(10px); } to { opacity: 1; transform: translateY(0); } } .code-block { background-color: #1e293b; /\* slate-800 \*/ color: #e2e8f0; /\* slate-200 \*/ border-radius: 0.5rem; padding: 1rem; overflow-x: auto; } .concept-card { background-color: white; border-radius: 0.75rem; box-shadow: 0 4px 6px -1px rgb(0 0 0 / 0.1), 0 2px 4px -2px rgb(0 0 0 / 0.1); margin-bottom: 1.5rem; overflow: hidden; }

C++ 핵심 개념
=========

[함수 (Functions)](#functions) [배열과 문자열](#arrays) [포인터와 참조](#pointers)

함수 (Functions)
==============

함수는 특정 작업을 수행하는 코드 블록을 하나로 묶은 것입니다. 코드를 논리적인 단위로 나누어 재사용성을 높이고 가독성을 향상시켜 프로그램의 구조를 체계적으로 만듭니다.

### 함수 정의 및 호출

**정의**는 함수가 수행할 작업을 코드로 작성하는 것이고, **호출**은 정의된 함수를 실행하도록 요청하는 것입니다.

    #include <iostream>
    // 두 정수를 받아 합을 반환하는 add 함수 정의
    int add(int a, int b) {
        return a + b;
    }
    
    int main() {
        // add 함수 호출
        int result = add(5, 10); 
        std::cout << "두 수의 합: " << result << std::endl; // 출력: 15
        return 0;
    }

### 매개변수 전달 방식

**값에 의한 호출(Pass-by-Value)**은 변수의 값을 복사하여 전달하므로 원본이 바뀌지 않습니다. **참조에 의한 호출(Pass-by-Reference)**은 변수의 주소를 전달하여 함수 내에서 원본 값을 직접 변경할 수 있습니다.

    void incrementByValue(int n) { n++; } // 원본 불변
    void incrementByReference(int& n) { n++; } // 원본 변경
    
    int main() {
        int a = 10, b = 10;
        incrementByValue(a);
        incrementByReference(b);
        std::cout << "값 호출 후 a: " << a << std::endl;   // 출력: 10
        std::cout << "참조 호출 후 b: " << b << std::endl; // 출력: 11
    }

### 함수 오버로딩 (Function Overloading)

이름이 같더라도 매개변수의 타입이나 개수가 다르면 서로 다른 함수로 인식하는 기능입니다. 동일한 기능에 대해 다양한 데이터 타입을 지원할 수 있어 편리합니다.

    // 정수 덧셈
    int add(int a, int b) { return a + b; }
    // 실수 덧셈
    double add(double a, double b) { return a + b; }
    
    int main() {
        std::cout << add(5, 3) << std::endl;       // int 버전 호출
        std::cout << add(5.5, 3.3) << std::endl; // double 버전 호출
    }

### 재귀 함수 (Recursive Function)

함수가 자기 자신을 다시 호출하는 구조입니다. 복잡한 문제를 동일한 구조의 더 작은 문제로 나누어 해결할 때 유용하며, 반드시 재귀를 멈추는 종료 조건이 필요합니다.

    long long factorial(int n) {
        if (n <= 1) return 1; // 종료 조건
        return n * factorial(n - 1); // 재귀 호출
    }
    
    int main() {
        std::cout << "5! = " << factorial(5) << std::endl; // 출력: 120
    }

배열과 문자열
=======

배열은 동일한 타입의 여러 데이터를 순차적으로 저장하는 가장 기본적인 자료구조입니다. C++에서는 전통적인 C-스타일 문자열과 현대적인 \`std::string\` 클래스를 모두 사용할 수 있습니다.

### 1차원 및 다차원 배열

**1차원 배열**은 데이터를 한 줄로, **다차원 배열**은 데이터를 행과 열의 테이블 형태로 저장합니다. 인덱스는 항상 0부터 시작합니다.

    // 1차원 배열
    int scores[5] = {100, 90, 85, 95, 80};
    std::cout << "3번째 점수: " << scores[2] << std::endl; // 출력: 85
    
    // 2차원 배열 (2행 3열)
    int matrix[2][3] = { {1, 2, 3}, {4, 5, 6} };
    std::cout << "matrix[1][2] 값: " << matrix[1][2] << std::endl; // 출력: 6

### C-스타일 문자열 vs \`std::string\`

**C-스타일 문자열**은 \`char\` 배열이며 끝을 널 문자(\`\\0\`)로 표시합니다. **\`std::string\`**은 길이를 자동으로 관리하고 다양한 편의 함수를 제공하는 C++의 표준 문자열 클래스로, 사용이 훨씬 안전하고 편리합니다.

    #include <string>
    
    // C-스타일 문자열
    char c_str[] = "Hello";
    
    // C++ 표준 문자열
    std::string cpp_str = "World";
    
    // std::string은 + 연산자로 쉽게 합칠 수 있음
    std::string greeting = std::string(c_str) + " " + cpp_str;
    std::cout << greeting << std::endl; // 출력: Hello World

포인터와 참조
=======

메모리를 직접 제어할 수 있는 C++의 강력하고 핵심적인 기능입니다. 포인터는 메모리 주소를, 참조는 변수의 별명을 나타내며, 동적 메모리 할당과 효율적인 데이터 처리에 필수적입니다.

### 포인터(\`\*\`)와 참조(\`&\`)

**포인터**는 변수의 메모리 주소를 저장하는 변수입니다. **참조**는 이미 존재하는 변수에 대한 또 다른 이름(별명)으로, 선언 시 반드시 초기화되어야 합니다.

    int number = 10;
    int* ptr = &number; // ptr은 number의 주소를 저장
    int& ref = number;  // ref는 number의 별명
    
    *ptr = 20; // 포인터로 원본 변경 -> number는 20이 됨
    ref = 30;  // 참조로 원본 변경 -> number는 30이 됨
    std::cout << "최종 number: " << number << std::endl; // 출력: 30

### 동적 메모리 할당 (\`new\`, \`delete\`)

프로그램 실행 중에 필요한 만큼 힙(Heap) 메모리를 할당(\`new\`)하고 해제(\`delete\`)하는 기능입니다. 사용이 끝난 메모리는 반드시 해제하여 메모리 누수를 방지해야 합니다.

    // 정수 배열 5개를 동적 할당
    int* p_arr = new int[5];
    p_arr[2] = 30; // 사용
    delete[] p_arr; // 반드시 배열 형태로 해제
    
    // 유효하지 않은 포인터는 nullptr로 초기화하는 것이 안전
    p_arr = nullptr;

### 포인터와 배열

배열의 이름은 배열의 첫 번째 원소를 가리키는 포인터처럼 동작합니다. 이를 이용해 포인터 연산으로 배열의 원소에 접근할 수 있습니다.

    int arr[5] = {10, 20, 30, 40, 50};
    int* ptr = arr; // ptr은 arr[0]을 가리킴
    
    // *(ptr + 2)는 arr[2]와 동일한 표현
    std::cout << "3번째 원소: " << *(ptr + 2) << std::endl; // 출력: 30

document.addEventListener('DOMContentLoaded', () => { const navMenu = document.getElementById('nav-menu'); const menuToggle = document.getElementById('menu-toggle'); const sidebar = document.getElementById('sidebar'); function switchView(hash) { document.querySelectorAll('.content-section').forEach(section => { section.classList.remove('active'); }); const activeSection = document.querySelector(hash); if (activeSection) { activeSection.classList.add('active'); } document.querySelectorAll('.nav-link').forEach(link => { link.classList.remove('active'); }); const activeLink = document.querySelector(\`.nav-link\[href="${hash}"\]\`); if (activeLink) { activeLink.classList.add('active'); } } navMenu.addEventListener('click', (e) => { if (e.target.tagName === 'A') { e.preventDefault(); const hash = e.target.getAttribute('href'); history.pushState(null, null, hash); switchView(hash); if (window.innerWidth < 640) { sidebar.classList.add('-translate-x-full'); } } }); menuToggle.addEventListener('click', () => { sidebar.classList.toggle('-translate-x-full'); }); window.addEventListener('popstate', () => { switchView(window.location.hash || '#functions'); }); switchView(window.location.hash || '#functions'); });