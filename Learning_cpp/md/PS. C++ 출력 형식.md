#  C / C++ 출력 형식 

##  개요
C와 C++은 **출력 형식을 세밀하게 제어**할 수 있는 기능을 제공  

1.  **C 스타일 (`printf`, `puts`)**
2.  **C++ 스타일 (`std::cout`, `<iomanip>`)**
3.  **C++20 이후 (`std::format`, `std::print`)**

---

#  1. C 스타일 (`printf`, `puts`)

##  `printf`
C 에서는 `printf()` 계열 함수를 사용하여 **서식 지정자(format specifier)** 로 출력 형식을 제어

```cpp
#include <stdio.h>

int main() {
    int n = 42;
    double pi = 3.141592;
    char *s = "hello";

    printf("정수: %d\n", n);
    printf("실수: %.2f\n", pi);
    printf("문자열: %s\n", s);
}
```

---

##  서식 지정자 종류류

| 형식 | 의미 | 예시 출력 |
|------|------|------------|
| `%d`, `%i` | 10진수 정수 | 42 |
| `%u` | 부호 없는 정수 | 42 |
| `%x`, `%X` | 16진수 (소/대문자) | 2a / 2A |
| `%o` | 8진수 | 52 |
| `%f` | 고정 소수점 실수 | 3.14 |
| `%e`, `%E` | 지수 표기법 | 3.14e+00 |
| `%g`, `%G` | 자동으로 `%f` 또는 `%e` 선택 | 3.14 |
| `%s` | 문자열 | hello |
| `%c` | 문자 | A |
| `%%` | `%` 문자 자체 | % |

---

##  폭(width)과 정밀도(precision)

| 서식 | 의미 | 예시 |
|------|------|------|
| `%5d` | 최소 폭 5칸 (오른쪽 정렬) | `"   42"` |
| `%-5d` | 왼쪽 정렬 | `"42   "` |
| `%05d` | 0으로 채움 | `"00042"` |
| `%8.3f` | 전체 폭 8칸, 소수점 3자리 | `"   3.142"` |

---

##  기타

| 옵션 | 의미 |
|------|------|
| `+` | 양수에 `+` 표시 |
| `#` | 진법 기호 표시 (`0x`, `0`) |
| (공백) | 양수 앞 공백 |
| `'` | 천 단위 구분자(일부 구현에서만 지원) |


```cpp
printf("%+d\n", 42);     // +42
printf("%#x\n", 255);    // 0xff
```

---

## `puts`
가장 단순하고 빠름, 문자열 끝에 **자동 개행(`\n`)**이 붙음, `printf`와 달리 문자열 내 `%` 등 포맷 문자가 있어도 그대로 출력됨

```cpp
#include <cstdio>

int main() {
    puts("Hello, world!");
}
```

---

#  2. C++ 스트림 출력 (`<iostream>`, `<iomanip>`)

C++은 **형식적인 스트림 기반 출력**

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double pi = 3.1415926535;
    cout << fixed << setprecision(3) << pi << endl; // 3.142
}
```

---

##  주요 manipulator

| 조정자 | 설명 |
|--------|------|
| `setprecision(n)` | 유효 숫자 or 소수점 이하 자리수 지정 |
| `fixed` | 고정 소수점 형식 |
| `scientific` | 지수 표기 형식 |
| `setw(n)` | 출력 폭 지정 |
| `setfill(ch)` | 채움 문자 지정 |
| `left`, `right` | 정렬 방향 |
| `showpos` | + 부호 표시 |
| `showpoint` | 소수점 강제 표시 |
| `hex`, `oct`, `dec` | 진법 지정 |
| `showbase` | 진법 접두어 (`0x`, `0`) 표시 |
| `boolalpha` | true/false로 출력 |
| `uppercase` | 대문자 표기 |
| `endl` | 줄바꿈 + flush |
| `flush` | flush만 수행 |

---

###  예시
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n = 255;
    double x = 12.3456;

    cout << hex << showbase << n << endl;       // 0xff
    cout << dec << setw(10) << setfill('-') << right << n << endl; // -------255
    cout << fixed << setprecision(2) << x << endl; // 12.35
}
```
---

## `std::cout.write()` 

바이트 단위 출력, 바이너리 데이터나 개행 없는 출력 가능, 길이를 직접 지정해야 함

```cpp
#include <iostream>
using namespace std;

int main() {
    const char* str = "Hello, world!";
    cout.write(str, 13);
}
```



---

#  3. C++20 이후 `std::format`, `std::print`

C++20부터는 Python 스타일의 **서식 문자열 기반 포맷팅**이 추가됨

```cpp
#include <format>
#include <iostream>

int main() {
    int n = 42;
    double pi = 3.141592;
    std::cout << std::format("정수: {}실수: {:.2f}", n, pi);
}
```

---

##  기본 문법
`{}` 안에 서식 명세

| 형식 | 의미 | 예시 |
|------|------|------|
| `{}` | 기본 출력 | 42 |
| `{:d}` | 10진수 정수 | 42 |
| `{:x}` | 16진수 | 2a |
| `{:08d}` | 폭 8칸, 0으로 채움 | 00000042 |
| `{:.2f}` | 소수점 이하 2자리 | 3.14 |
| `{:>8}` | 오른쪽 정렬 | `"      42"` |
| `{:<8}` | 왼쪽 정렬 | `"42      "` |
| `{:^8}` | 가운데 정렬 | `"   42   "` |
| `{:+}` | 부호 표시 | +42 |
| `{:b}` | 2진수 | 101010 |
| `{:#x}` | 접두어 포함 | 0x2a |
| `{:.3e}` | 지수 표기 | 3.142e+00 |

---

##  `std::print` (C++23)
C++23부터는 `std::format`과 비슷하지만, 바로 출력하는 `std::print()`가 추가됨

```cpp
#include <print>

int main() {
    std::print("안녕하세요, {}님!", "Devleu");
}
```

---

#  비교 요약

| 구분 | 방식 | 주요 특징 | 장점 | 단점 |
|------|------|-----------|------|------|
| **C (`printf`)** | 서식 지정자 기반 | 간결하고 빠름 | 성능 우수, 이식성 높음 | 타입 안전하지 않음 |
| **C++ (`iomanip`)** | 스트림 기반 | 조정자 사용 | 타입 안전, 유연함 | 문법이 장황 |
| **C++20 (`format`)** | 서식 문자열 기반 | `{}` 포맷 문법 | 직관적, 안전, 강력 | C++20 이상 필요 |

---

#  요약

| 범주 | C 스타일 | C++ iostream | C++20 format |
|------|-----------|--------------|---------------|
| **정수 출력** | `%d`, `%x`, `%o` | `hex`, `oct`, `dec` | `{:d}`, `{:x}`, `{:o}` |
| **실수 출력** | `%f`, `%e`, `%g` | `fixed`, `scientific`, `setprecision()` | `{:.2f}`, `{:.3e}` |
| **폭 지정** | `%5d`, `%-5d` | `setw()`, `left`, `right` | `{:>5}`, `:{:<5}` |
| **채움 문자** | `%05d` | `setfill('0')` | `{:05d}` |
| **부호 표시** | `%+d` | `showpos` | `{:+}` |
| **진법 접두어** | `%#x` | `showbase` | `{:#x}` |
| **정렬 방향** | `%-5d` | `left`, `right` | `{:<5}`, `{:>5}` |
| **불리언** | 없음 | `boolalpha` | `{}` |
| **문자열** | `%s` | 그대로 출력 | `{}` |

---

## `Raw String Literal`
문자열 내의 `\n`, `\t` 같은 **이스케이프 문자를 그대로 출력**하고 싶다면
**Raw String Literal**을 사용

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << R"(Hello\nWorld\t!)" << endl;
}
```

> 출력 결과
> ```
> Hello\nWorld\t!
> ```

---

#  참고 자료
- C Reference: [https://en.cppreference.com/w/c/io/fprintf](https://en.cppreference.com/w/c/io/fprintf)
- C++ Reference: [https://en.cppreference.com/w/cpp/io/manip](https://en.cppreference.com/w/cpp/io/manip)
- C++20 `std::format`: [https://en.cppreference.com/w/cpp/utility/format/format](https://en.cppreference.com/w/cpp/utility/format/format)
