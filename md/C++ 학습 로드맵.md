  C++ Interactive Learning Roadmap body { font-family: 'Inter', sans-serif; background-color: #f8fafc; /\* slate-50 \*/ } @import url('https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&family=Nanum+Gothic+Coding&display=swap'); .font-coding { font-family: 'Nanum Gothic Coding', monospace; } .nav-link { transition: all 0.2s ease-in-out; } .nav-link.active { background-color: #e0f2fe; /\* sky-100 \*/ color: #0c4a6e; /\* sky-900 \*/ font-weight: 600; } .nav-link:hover { background-color: #f0f9ff; /\* sky-50 \*/ } .content-section { display: none; } .content-section.active { display: block; } .tab-btn.active { border-bottom-color: #0ea5e9; /\* sky-500 \*/ color: #0284c7; /\* sky-600 \*/ } .project-card .details { transform: translateY(100%); transition: transform 0.3s ease-out; } .project-card:hover .details { transform: translateY(0); } .code-block { background-color: #1e293b; /\* slate-800 \*/ color: #e2e8f0; /\* slate-200 \*/ border-radius: 0.5rem; padding: 1rem; overflow-x: auto; }

C++ 학습 로드맵
==========

[소개](#intro)

모던 C++
------

[스마트 포인터](#smart-pointers) [람다 & auto](#lambda-auto) [이동 의미론 & 동시성](#move-concurrency)

실전 적용
-----

[프로젝트 진행](#projects) [심화 학습](#next-steps)

모던 C++와 다음 단계로의 로드맵
===================

이 문서는 C++11 이후 도입된 핵심적인 모던 C++ 기능들을 소개하고, 이를 바탕으로 실제 프로젝트를 진행하며 전문가로 성장하기 위한 학습 로드맵을 제시합니다. 좌측 메뉴를 통해 각 주제를 탐색하며 C++의 강력한 기능들을 학습해 보세요.

스마트 포인터 (Smart Pointers)
========================

스마트 포인터는 \`new\`와 \`delete\`를 수동으로 관리할 때 발생하는 메모리 누수 문제를 해결해주는 핵심 도구입니다. 객체의 \*\*소유권(ownership)\*\* 개념을 통해 포인터의 수명이 다하면 자동으로 메모리를 해제하여 코드를 더 안전하게 만들어 줍니다.

std::unique\_ptr std::shared\_ptr std::weak\_ptr

람다 표현식 & auto
=============

람다 표현식과 \`auto\` 키워드는 코드를 놀랍도록 간결하고 가독성 있게 만들어주는 모던 C++의 대표적인 기능입니다. 특히 STL 알고리즘과 함께 사용할 때 그 강력함이 드러납니다.

### 람다 표현식 (Lambda Expressions)

이름 없는 함수(익명 함수)를 인라인으로 간편하게 정의하는 방법입니다. STL 알고리즘에 필요한 조건자 함수 등을 그 자리에서 바로 작성할 수 있습니다.

    #include <iostream>
    #include <vector>
    #include <algorithm>
    
    int main() {
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
        int threshold = 3;
    
        // 람다를 사용하여 threshold보다 큰 첫 번째 원소 찾기
        auto it = std::find_if(numbers.begin(), numbers.end(), 
            [threshold](int n) { return n > threshold; }
        );
    
        if (it != numbers.end()) {
            std::cout << *it << std::endl; // 출력: 4
        }
        return 0;
    }
    

### \`auto\` 및 범위 기반 for 루프

\`auto\`는 컴파일러가 변수 타입을 자동으로 추론하게 하여 복잡한 타입 이름을 대체하고, 범위 기반 for 루프는 컨테이너를 순회하는 코드를 매우 단순하게 만들어 줍니다.

    #include <iostream>
    #include <map>
    #include <string>
    
    int main() {
        std::map<std::string, int> scores;
        scores["Alice"] = 90;
        scores["Bob"] = 85;
    
        // auto와 범위 기반 for 루프로 map 순회
        for (const auto& pair : scores) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
        return 0;
    }
    

이동 의미론 & 동시성
============

C++의 성능을 극한으로 끌어올리고 현대적인 멀티코어 환경을 최대한 활용하기 위한 고급 개념들입니다. 이 기능들을 통해 더 빠르고 효율적인 애플리케이션을 만들 수 있습니다.

### 이동 의미론 (Move Semantics)

불필요한 데이터 복사를 피하고 객체의 리소스(메모리 등) 소유권을 '이동'시키는 개념입니다. 임시 객체나 더 이상 필요 없는 객체의 데이터를 복사하는 대신 효율적으로 전달하여 성능을 향상시킵니다. \`std::move\`를 통해 명시적으로 사용됩니다.

### 동시성 프로그래밍 (Concurrency)

여러 작업을 동시에 실행하여 프로그램 성능을 높이는 기법입니다. 아래 도구들을 사용해 멀티스레드 프로그래밍을 구현할 수 있습니다.

*   `std::thread`: 스레드를 생성하고 관리합니다.
*   `std::mutex`: 공유 데이터에 대한 동시 접근을 막는 잠금 장치입니다.
*   `std::future`: 비동기 작업의 결과를 받아오는 도구입니다.

프로젝트 진행
=======

이론 학습을 넘어 실제 문제 해결 능력을 기르기 위해 작은 프로젝트를 시작하는 것이 중요합니다. 카드 위에 마우스를 올려 적용할 수 있는 핵심 개념들을 확인해 보세요.

### 콘솔 기반 게임

텍스트 RPG, 테트리스, 스네이크

#### 적용 개념

*   객체 지향 프로그래밍 (OOP)
*   STL 컨테이너
*   파일 입출력 (게임 저장)

### 주소록 관리 프로그램

연락처 추가, 검색, 삭제 기능

#### 적용 개념

*   클래스와 객체
*   std::map 또는 std::vector
*   파일 입출력 (CSV/TXT)

### 간단한 라이브러리

자신만의 자료구조 또는 유틸리티

#### 적용 개념

*   템플릿 (Templates)
*   캡슐화 (Encapsulation)
*   네임스페이스

심화 학습
=====

기본기와 프로젝트 경험을 쌓았다면, 더 전문적인 개발자로 성장하기 위한 다음 단계들을 탐색해 보세요.

### 디자인 패턴 (Design Patterns)

소프트웨어 설계에서 반복적으로 발생하는 문제들에 대한 검증된 해결책입니다. (예: 싱글톤, 팩토리, 옵저버 패턴) 유지보수가 쉽고 유연한 코드를 작성하는 데 필수적입니다.

### 특정 분야 학습

자신의 관심사와 목표에 맞는 전문 분야를 선택하여 깊이 있게 학습합니다.

*   **게임 개발:** 언리얼 엔진(Unreal Engine)
*   **시스템 프로그래밍:** 운영체제, 네트워크 등 저수준 프로그래밍
*   **임베디드 시스템:** 제한된 자원을 가진 하드웨어 제어
*   **고성능 컴퓨팅 (HPC):** 금융, 과학 계산 등 최고 성능 요구 분야

### 빌드 시스템 및 버전 관리

현대적인 개발 환경에서 협업과 프로젝트 관리를 위한 필수 도구입니다.

*   **CMake:** 여러 플랫폼에서 C++ 프로젝트를 빌드하고 관리하는 표준 도구
*   **Git:** 코드의 변경 이력을 관리하고 협업하기 위한 필수 버전 관리 시스템

const smartPointersData = { unique\_ptr: { title: 'std::unique\_ptr: 유일한 소유권', description: '오직 하나의 \`unique\_ptr\`만이 특정 객체를 소유할 수 있습니다. 복사가 불가능하며, 소유권 이전은 \`std::move\`를 통해 가능합니다. 포인터가 범위를 벗어나면 자동으로 메모리를 해제하여 가장 간단하고 안전한 메모리 관리를 제공합니다.', code: \`#include <iostream>\\n#include <memory>\\n\\nclass MyClass {\\npublic:\\n MyClass() { std::cout << "MyClass 생성됨\\\\n"; }\\n ~MyClass() { std::cout << "MyClass 소멸됨\\\\n"; }\\n void doSomething() { std::cout << "작업 수행!\\\\n"; }\\n};\\n\\nint main() {\\n {\\n std::unique\_ptr<MyClass> u\_ptr = std::make\_unique<MyClass>();\\n u\_ptr->doSomething();\\n } // <-- 여기서 u\_ptr이 소멸되며 메모리도 해제됨\\n std::cout << "unique\_ptr 범위 벗어남\\\\n";\\n return 0;\\n}\` }, shared\_ptr: { title: 'std::shared\_ptr: 공유된 소유권', description: '여러 \`shared\_ptr\`가 하나의 객체를 함께 소유할 수 있습니다. 참조 카운트(reference count)를 통해 객체를 가리키는 포인터의 수를 세고, 이 카운트가 0이 되면 메모리를 해제합니다. 여러 곳에서 객체의 수명을 공유해야 할 때 유용합니다.', code: \`#include <iostream>\\n#include <memory>\\n\\nclass MyClass { /\*...\*/ };\\n\\nint main() {\\n std::shared\_ptr<MyClass> s\_ptr1;\\n {\\n std::shared\_ptr<MyClass> s\_ptr2 = std::make\_shared<MyClass>();\\n s\_ptr1 = s\_ptr2; // 참조 카운트가 2가 됨\\n std::cout << "참조 카운트: " << s\_ptr1.use\_count() << "\\\\n";\\n } // s\_ptr2 소멸. 참조 카운트는 1\\n std::cout << "참조 카운트: " << s\_ptr1.use\_count() << "\\\\n";\\n return 0; // s\_ptr1 소멸. 참조 카운트 0, 객체 소멸\\n}\` }, weak\_ptr: { title: 'std::weak\_ptr: 약한 참조', description: '\`shared\_ptr\`의 순환 참조 문제를 해결하기 위해 사용됩니다. 객체를 소유하지는 않으면서(참조 카운트를 증가시키지 않음) 관찰만 하는 포인터입니다. 객체에 접근하기 전에는 \`lock()\` 메소드를 통해 유효한 \`shared\_ptr\`를 얻어와야 합니다.', code: \`#include <iostream>\\n#include <memory>\\n\\nint main() {\\n std::shared\_ptr<int> sp = std::make\_shared<int>(42);\\n std::weak\_ptr<int> wp = sp;\\n\\n std::cout << "참조 카운트: " << sp.use\_count() << "\\\\n"; // 1\\n\\n if (auto locked\_sp = wp.lock()) { // 유효한지 확인하고 shared\_ptr로 변환\\n std::cout << "객체 값: " << \*locked\_sp << "\\\\n";\\n std::cout << "참조 카운트: " << sp.use\_count() << "\\\\n"; // 2\\n } // locked\_sp 소멸. 참조 카운트 1\\n\\n sp.reset(); // sp가 가리키는 객체 해제\\n\\n if (wp.expired()) {\\n std::cout << "weak\_ptr이 가리키는 객체가 소멸되었습니다.\\\\n";\\n }\\n\\n return 0;\\n}\` } }; function updateSmartPointerContent(type) { const data = smartPointersData\[type\]; const contentDiv = document.getElementById('smart-pointers-content'); contentDiv.innerHTML = \` <div class="bg-white p-6 rounded-lg shadow-sm"> <h3 class="text-xl font-semibold mb-2">${data.title}</h3> <p class="mb-4 text-slate-600">${data.description}</p> <div class="code-block font-coding"> <pre><code>${data.code.replace(/</g, "&lt;").replace(/>/g, "&gt;")}</code></pre> </div> </div> \`; } function switchView(hash) { document.querySelectorAll('.content-section').forEach(section => { section.classList.remove('active'); }); const activeSection = document.querySelector(hash); if(activeSection) { activeSection.classList.add('active'); } document.querySelectorAll('.nav-link').forEach(link => { link.classList.remove('active'); }); const activeLink = document.querySelector(\`.nav-link\[href="${hash}"\]\`); if(activeLink) { activeLink.classList.add('active'); } if (hash === '#smart-pointers') { const initialTab = document.querySelector('#smart-pointers-tabs .tab-btn.active'); updateSmartPointerContent(initialTab.dataset.target); } } document.addEventListener('DOMContentLoaded', () => { const navMenu = document.getElementById('nav-menu'); const smartPointersTabs = document.getElementById('smart-pointers-tabs'); const menuToggle = document.getElementById('menu-toggle'); const sidebar = document.getElementById('sidebar'); navMenu.addEventListener('click', (e) => { if (e.target.tagName === 'A') { e.preventDefault(); const hash = e.target.getAttribute('href'); window.location.hash = hash; if(window.innerWidth < 640) { // sm breakpoint sidebar.classList.add('-translate-x-full'); } } }); if (smartPointersTabs) { smartPointersTabs.addEventListener('click', (e) => { if (e.target.classList.contains('tab-btn')) { smartPointersTabs.querySelector('.active').classList.remove('active'); e.target.classList.add('active'); updateSmartPointerContent(e.target.dataset.target); } }); } menuToggle.addEventListener('click', () => { sidebar.classList.toggle('-translate-x-full'); }); window.addEventListener('hashchange', () => { switchView(window.location.hash || '#intro'); }); // Initial view switchView(window.location.hash || '#intro'); });