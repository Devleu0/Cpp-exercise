# C++ 헤더 파일과 소스 파일 관리 가이드

### 목차
1. [소개](#introduce)
2. [헤더 파일](#header-file)
3. [소스 파일](#source-file)
4. [전처리기](#header-and-source-file-management-principles)
5. [프로젝트 구조](#project-structure-example)
6. [환경](#environment-differences)


## 1. 소개  <a name="introduce"></a>
C++ 프로젝트에서 파일 관리는 코드의 유지보수성과 확장성을 높이는 중요한 요소입니다.  
헤더 파일과 소스 파일을 적절히 나누어 관리하면 컴파일 시간 단축, 코드 재사용성 증가, 의존성 관리가 쉬워집니다.

---

## 2. 헤더 파일(.h/.hpp)이란? <a name="header-file"></a>
헤더 파일은 클래스, 함수, 상수, 매크로 선언 등 인터페이스(interface)를 정의하는 파일입니다.  
헤더 파일은 일반적으로 구현(implementation)을 포함하지 않고, 선언(declaration)만 포함합니다.

### 헤더 파일의 목적
- 함수와 클래스의 선언을 분리하여 코드 재사용성을 높임.
- 코드의 인터페이스(interface)를 명확히 함.
- 여러 소스 파일에서 동일한 선언을 공유 가능하게 함.

### 헤더 파일 예시
```cpp
// MathUtils.h
#pragma once  // Include guard 역할

class MathUtils {
public:
    static int add(int a, int b);
    static int subtract(int a, int b);
};
````

---

## 3. 소스 파일(.cpp)이란? <a name="source-file"></a>

소스 파일은 구현(implementation)을 포함합니다.
헤더 파일에서 선언한 함수나 클래스의 실제 동작을 작성하는 곳입니다.

### 소스 파일 예시

```cpp
// MathUtils.cpp
#include "MathUtils.h"

int MathUtils::add(int a, int b) {
    return a + b;
}

int MathUtils::subtract(int a, int b) {
    return a - b;
}
```

---

## 4. 전처리기 작성 순서와 기능 <a name="header-and-source-file-management-principles"></a>

전처리기는 소스 코드 작성 시 특정 순서와 규칙을 지켜야 합니다. 

| 순서 | 전처리 지시문 | 기능 |
|------|--------------|------|
| 1    | `#ifndef`, `#define`, `#pragma once` | 헤더 가드: 헤더 파일이 여러 번 포함되는 것을 방지. 동일 헤더가 두 번 이상 포함될 때 컴파일 오류 방지. |
| 2    | `#include` | 헤더 파일 포함: 다른 파일(표준, 외부, 사용자 정의)을 현재 파일에 삽입. 포함 순서가 중요함. |
| 3    | `#define` | 매크로 정의: 상수값, 심볼, 조건부 컴파일 플래그 정의. |
| 4    | `#undef` | 매크로 해제: 이전에 정의한 매크로 제거. |
| 5    | `#if`, `#ifdef`, `#ifndef`, `#else`, `#elif`, `#endif` | 조건부 컴파일: 컴파일할 코드 블록을 조건에 따라 선택적으로 포함 또는 제외. |
| 6    | `#error` | 컴파일 에러 강제 발생: 특정 조건을 만족하지 않을 때 에러 메시지 출력. |
| 7    | `#line` | 라인 번호/파일 이름 지정: 디버깅 또는 자동 생성 코드에서 유용. |
| 8    | `#pragma` | 컴파일러 제어: 경고 무시, 최적화 제어, 플랫폼별 지시 등. |

---

### 헤더(.h) 파일

```cpp
#ifndef MYHEADER_H         // 1. 헤더 가드 시작
#define MYHEADER_H

#include <iostream>        // 2. 표준 라이브러리 헤더
#include "MyLib.h"         // 2. 사용자 정의 헤더

#define VERSION 1.0        // 3. 매크로 정의
#undef OLD_VERSION         // 4. 매크로 해제

#ifdef DEBUG              // 5. 조건부 컴파일
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif

#pragma once             // 8. 컴파일러 지시

#endif // MYHEADER_H    // 1. 헤더 가드 닫기
```

---

### 소스(.cpp) 파일

```cpp
#include "MyHeader.h"     // 2. 헤더 포함

#define DEBUG              // 3. 매크로 정의

#ifdef DEBUG              // 5. 조건부 컴파일
    LOG("디버그 모드 활성화");
#endif

int main() {
    std::cout << "Hello World" << std::endl;
    return 0;
}
```
## 4.1. 헤더와 소스 파일 관리 원칙 
### 1. 선언과 구현 분리

* 함수 선언은 헤더 파일에 작성.
* 함수 구현은 소스 파일에 작성.
* 이렇게 하면 컴파일 시간과 의존성을 줄일 수 있음.

### 2. Include Guard 또는 `#pragma once` 사용

* 헤더 파일이 여러 번 포함되는 문제 방지.

```cpp
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// 선언

#endif // MATH_UTILS_H
```

또는

```cpp
#pragma once
```

### 3. 최소한의 Include

* 헤더 파일에는 꼭 필요한 선언만 포함.
* 구현 관련 헤더는 소스 파일에서 include.
* 전방 선언(forward declaration)을 적극 활용.

### 4. 네이밍 규칙

* 헤더 파일: `.h` 또는 `.hpp` 확장자.
* 소스 파일: `.cpp` 확장자.
* 클래스명과 파일명 일치 권장.

---

## 5. 프로젝트 구조 예시 <a name="project-structure-example"></a>


```
Project/
│
├── include/           # 헤더 파일
│   ├── MathUtils.h
│   └── Logger.h
│
├── src/               # 소스 파일
│   ├── MathUtils.cpp
│   └── Logger.cpp
│
├── main.cpp          # 엔트리 포인트
│
└── CMakeLists.txt    # 빌드 스크립트
```

---

#### main.cpp

```cpp
#include <iostream>
#include "MathUtils.h"

int main() {
    int result = MathUtils::add(10, 20);
    std::cout << "10 + 20 = " << result << std::endl;
    return 0;
}
```

## 6. 개발 환경에서 <a name="environment-differences"></a>
### GCC 예시
---
```bash
g++ -Iinclude src/MathUtils.cpp main.cpp -o myprogram
```

* `-Iinclude` : 헤더 파일 위치 지정.
* `src/MathUtils.cpp main.cpp` : 컴파일할 소스 파일 지정.


### Visual Studio 환경에서의 헤더/소스 관리
---
### 1. 프로젝트 생성

* Visual Studio에서 File → New → Project 선택.
* "Console App" 또는 "Empty Project" 선택.
* 프로젝트 이름 및 위치 지정 후 생성.

### 2. 헤더/소스 파일 추가

* Solution Explorer에서 프로젝트를 선택.
* 오른쪽 클릭 → Add → New Item 선택.
* Header File (.h/.hpp) 또는 C++ File (.cpp) 선택.
* 파일명을 지정하고 추가.

### 3. Include Path 설정

* 헤더 파일을 `include` 폴더에 넣으면, 프로젝트 속성에서 C/C++ → General → Additional Include Directories에 해당 폴더 경로를 추가.
* 이렇게 하면 `#include "MathUtils.h"`처럼 상대 경로 없이 불러올 수 있음.

### 4. 빌드 및 실행

* Visual Studio의 Build → Build Solution 또는 단축키 `Ctrl+Shift+B`로 빌드.
* Debug → Start Debugging(F5) 또는 `Ctrl+F5`로 실행.

### 5. 장점

* IDE에서 자동으로 파일 관리.
* IntelliSense로 빠른 코드 완성 및 오류 확인.
* 디버깅 및 빌드 관리가 쉬움.

