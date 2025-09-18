  고급 C++ 인터랙티브 대시보드 @import url('https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&family=Nanum+Gothic+Coding&display=swap'); body { font-family: 'Inter', sans-serif; background-color: #f1f5f9; /\* slate-100 \*/ } .font-coding { font-family: 'Nanum Gothic Coding', monospace; } .nav-link { transition: all 0.2s ease-in-out; } .nav-link.active { background-color: #e0f2fe; /\* sky-100 \*/ color: #0c4a6e; /\* sky-900 \*/ font-weight: 600; } .nav-link:hover:not(.active) { background-color: #f0f9ff; /\* sky-50 \*/ } .content-section { display: none; } .content-section.active { display: block; animation: fadeIn 0.5s ease-in-out; } @keyframes fadeIn { from { opacity: 0; transform: translateY(10px); } to { opacity: 1; transform: translateY(0); } } .code-block { background-color: #1e293b; /\* slate-800 \*/ color: #e2e8f0; /\* slate-200 \*/ border-radius: 0 0 0.75rem 0.75rem; padding: 1rem; overflow-x: auto; } .concept-card { background-color: white; border-radius: 0.75rem; box-shadow: 0 4px 6px -1px rgb(0 0 0 / 0.1), 0 2px 4px -2px rgb(0 0 0 / 0.1); margin-bottom: 1.5rem; overflow: hidden; }

고급 C++ 프로그래밍
============

[템플릿](#templates) [표준 템플릿 라이브러리](#stl) [예외 처리](#exceptions) [파일 입출력](#file-io)

1\. 템플릿 (Templates)
===================

템플릿은 데이터 타입에 의존하지 않는 일반화된 코드를 작성하게 해주는 C++의 핵심 기능입니다. 템플릿을 사용하면 하나의 함수나 클래스로 정수, 실수, 문자열 등 다양한 타입을 처리할 수 있어 코드 재사용성이 극대화됩니다.

### 함수 템플릿 (Function Templates)

하나의 함수 정의로 여러 다른 타입의 인자를 처리할 수 있는 함수를 만듭니다. 컴파일러가 함수 호출 시점의 인자 타입을 보고 자동으로 적절한 타입의 함수를 생성해 줍니다.

    #include <iostream>
    
    template <typename T>
    T add(T a, T b) {
        return a + b;
    }
    
    int main() {
        std::cout << "정수 덧셈: " << add(5, 10) << std::endl;
        std::cout << "실수 덧셈: " << add(3.5, 7.2) << std::endl;
    }

### 클래스 템플릿 (Class Templates)

특정 데이터 타입에 국한되지 않는 일반화된 클래스를 정의합니다. 이를 통해 정수를 담는 Box, 문자열을 담는 Box 등을 동일한 클래스 설계도로 만들 수 있습니다.

    #include <iostream>
    #include <string>
    
    template <typename T>
    class Box {
    private:
        T content;
    public:
        void setContent(T newContent) { content = newContent; }
        T getContent() { return content; }
    };
    
    int main() {
        Box<int> intBox;
        intBox.setContent(123);
        std::cout << "intBox 내용: " << intBox.getContent() << std::endl;
    
        Box<std::string> stringBox;
        stringBox.setContent("Hello World");
        std::cout << "stringBox 내용: " << stringBox.getContent() << std::endl;
    }

2\. 표준 템플릿 라이브러리 (STL)
======================

STL은 C++ 프로그래머를 위해 미리 만들어진 강력한 도구 모음입니다. 자주 사용되는 자료구조와 알고리즘이 템플릿 기반으로 구현되어 있어, 어떤 데이터 타입이든 일관된 방식으로 다룰 수 있습니다.

### STL의 3대 구성 요소

*   **컨테이너 (Containers):** `vector`, `map`, `set`처럼 데이터를 저장하는 자료구조입니다.
*   **반복자 (Iterators):** 컨테이너의 원소를 순회하고 접근하게 해주는 포인터와 유사한 객체입니다.
*   **알고리즘 (Algorithms):** `sort`, `find`처럼 데이터에 적용할 수 있는 일반화된 함수입니다.

    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <map>
    
    int main() {
        // vector 컨테이너와 sort 알고리즘 사용
        std::vector<int> numbers = {30, 10, 50, 20, 40};
        std::sort(numbers.begin(), numbers.end());
    
        std::cout << "정렬된 숫자: ";
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    
        // map 컨테이너 사용
        std::map<std::string, int> scores;
        scores["홍길동"] = 95;
        std::cout << "홍길동의 점수: " << scores["홍길동"] << std::endl;
    }

3\. 예외 처리 (Exception Handling)
==============================

프로그램 실행 중 예기치 않은 오류가 발생했을 때, 프로그램이 비정상적으로 종료되는 것을 막고 안정적으로 대처하는 메커니즘입니다. 오류 발생 가능성이 있는 코드를 \`try\` 블록으로 감싸고, \`catch\` 블록에서 오류를 처리합니다.

### \`try-catch\`를 이용한 오류 처리

\`divide\` 함수에서 0으로 나누려는 시도가 발생하면 \`throw\`를 통해 예외를 던집니다. \`main\` 함수의 \`try\` 블록 안에서 이 예외가 발생하면, 프로그램은 즉시 해당 \`catch\` 블록으로 이동하여 오류를 처리하고 실행을 계속합니다.

    #include <iostream>
    #include <stdexcept>
    
    double divide(double a, double b) {
        if (b == 0) {
            throw std::runtime_error("0으로 나눌 수 없습니다!");
        }
        return a / b;
    }
    
    int main() {
        try {
            double result = divide(10.0, 0.0);
            std::cout << "결과: " << result << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "오류 발생: " << e.what() << std::endl;
        }
        std::cout << "프로그램은 계속됩니다." << std::endl;
    }

4\. 파일 입출력 (File I/O)
=====================

\`\` 라이브러리를 사용하면 프로그램 외부의 파일에 데이터를 쓰거나, 파일로부터 데이터를 읽어올 수 있습니다. 이는 프로그램의 데이터를 영구적으로 저장하거나 외부 데이터를 처리하는 데 필수적입니다.

### 파일 쓰고 읽기

\`ofstream\` 객체를 사용하여 "my\_document.txt" 파일에 텍스트를 씁니다. 그 후 \`ifstream\` 객체를 사용하여 방금 쓴 파일의 내용을 다시 읽어와 콘솔에 출력합니다.

    #include <iostream>
    #include <fstream>
    #include <string>
    
    int main() {
        std::string filename = "my_document.txt";
    
        // 파일 쓰기
        {
            std::ofstream ofs(filename);
            ofs << "안녕하세요, C++ 파일 입출력입니다." << std::endl;
            std::cout << filename << " 파일 쓰기 완료." << std::endl;
        }
    
        // 파일 읽기
        {
            std::ifstream ifs(filename);
            std::string line;
            std::cout << "\n--- 파일 내용 읽기 ---" << std::endl;
            while (std::getline(ifs, line)) {
                std::cout << line << std::endl;
            }
        }
        return 0;
    }

document.addEventListener('DOMContentLoaded', () => { const navMenu = document.getElementById('nav-menu'); const menuToggle = document.getElementById('menu-toggle'); const sidebar = document.getElementById('sidebar'); function switchView(hash) { document.querySelectorAll('.content-section').forEach(section => { section.classList.remove('active'); }); const activeSection = document.querySelector(hash); if (activeSection) { activeSection.classList.add('active'); } document.querySelectorAll('.nav-link').forEach(link => { link.classList.remove('active'); }); const activeLink = document.querySelector(\`.nav-link\[href="${hash}"\]\`); if (activeLink) { activeLink.classList.add('active'); } } navMenu.addEventListener('click', (e) => { if (e.target.tagName === 'A') { e.preventDefault(); const hash = e.target.getAttribute('href'); history.pushState(null, null, hash); switchView(hash); if (window.innerWidth < 640) { sidebar.classList.add('-translate-x-full'); } } }); menuToggle.addEventListener('click', () => { sidebar.classList.toggle('-translate-x-full'); }); window.addEventListener('popstate', () => { switchView(window.location.hash || '#templates'); }); switchView(window.location.hash || '#templates'); });