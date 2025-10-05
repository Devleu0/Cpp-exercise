
# C++ 문자열 다루기

## 1. 문자열 선언 및 초기화

```cpp
#include <string>

std::string s1 = "Hello";
std::string s2("World");
std::string s3 = s1 + " " + s2;   // 문자열 연결
std::string s4(5, '*');           // ***** (문자 5번 반복)
```

---

## 2. 문자열 입력과 출력

```cpp
std::string s;
std::cin >> s;              // 공백 전까지 입력
std::getline(std::cin, s);  // 한 줄 전체 입력

std::cout << s << std::endl;
```

---

## 3. 길이 확인

```cpp
s.length(); // 또는 s.size();
```

---

## 4. 문자 접근 (인덱스)

```cpp
std::string s = "apple";
char c1 = s[0];       // 'a'
char c2 = s.at(1);    // 'p' (범위 검사 포함)

s[0] = 'A';           // 수정 가능
```

---

## 5. 부분 문자열 (substr)

```cpp
std::string s = "HelloWorld";
std::string sub = s.substr(0, 5);  // "Hello"
std::string tail = s.substr(5);    // "World"
```



---

## 6. 문자열 비교

```cpp
std::string a = "apple";
std::string b = "banana";

if (a == b) { }          // 같은지 비교
if (a != b) { }          // 다른지 비교
if (a < b) { }           // 사전순 비교

a.compare(b);            // <0, =0, >0 반환
```

---

## 7. 문자열 결합 및 추가

```cpp
std::string s = "Hello";
s += " World";           // "Hello World"
s.append("!!!");         // "Hello World!!!"

std::string a = "A", b = "B";
std::string c = a + b;   // "AB"
```

---

## 8. 삽입 (insert)

```cpp
std::string s = "World";
s.insert(0, "Hello ");   // "Hello World"
```

---

## 9. 삭제 (erase)

```cpp
std::string s = "Hello World";
s.erase(5, 1);  // 인덱스 5부터 1글자 삭제 => "HelloWorld"
s.clear();      // 전체 삭제
```

---

## 10. 교체 (replace)

```cpp
std::string s = "I like apple";
s.replace(7, 5, "banana");  // "I like banana"
```

---

## 11. 찾기 (find, rfind)

```cpp
std::string s = "banana";
size_t pos = s.find("na");    // 2
size_t rpos = s.rfind("na");  // 4 (뒤에서 찾기)

if (pos != std::string::npos) {
    // 찾은 경우
}
```

---

## 12. 특정 문자 찾기 (find_first_of, find_last_of)

```cpp
std::string s = "abcdef";
s.find_first_of("cd");  // 2
s.find_last_of("cd");   // 3
```

---

## 13. 구분자 기준 분리

C++에는 기본 `split()`이 없습니다.
아래는 `std::getline()`과 `stringstream`을 사용한 구현 예시입니다.

```cpp
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

// 사용
auto parts = split("apple,orange,banana", ',');
```

---

## 14. 대소문자 변환

```cpp
#include <algorithm>
#include <cctype>

std::string s = "Hello";
std::transform(s.begin(), s.end(), s.begin(), ::toupper); // "HELLO"
std::transform(s.begin(), s.end(), s.begin(), ::tolower); // "hello"
```

---

## 15. 문자열 뒤집기

```cpp
#include <algorithm>

std::string s = "abc";
std::reverse(s.begin(), s.end()); // "cba"
```

---

## 16. 공백 제거

C++ 표준에는 `trim()`이 없습니다. 직접 구현해야 합니다.

```cpp
#include <string>
#include <algorithm>
#include <cctype>

std::string trim(const std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) start++;

    auto end = s.end();
    do { end--; } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}
```

---

## 17. 문자열 비교 (대소문자 무시)

```cpp
#include <algorithm>
#include <cctype>

bool iequals(const std::string& a, const std::string& b) {
    if (a.size() != b.size()) return false;
    return std::equal(a.begin(), a.end(), b.begin(),
                      [](char x, char y) {
                          return std::tolower(x) == std::tolower(y);
                      });
}
```

---

## 18. 문자열을 숫자로 변환

```cpp
#include <string>

int n = std::stoi("123");
long l = std::stol("12345");
double d = std::stod("3.14");
```

---

## 19. 숫자를 문자열로 변환

```cpp
int n = 42;
std::string s = std::to_string(n); // "42"
```

---

## 20. 문자열 결합 시 성능 최적화 (stringstream)

```cpp
#include <sstream>

std::stringstream ss;
ss << "Hello " << "World " << 123;
std::string result = ss.str(); // "Hello World 123"
```

---

## 24. 반복자 기반 접근

```cpp
std::string s = "abcd";
for (auto it = s.begin(); it != s.end(); ++it) {
    std::cout << *it;
}
```

---

## 25. 문자열 정렬

```cpp
#include <algorithm>

std::string s = "dcba";
std::sort(s.begin(), s.end()); // "abcd"
```

---

## 요약 표

| 기능     | 함수/방법                   | 예시                              |
| ------ | ----------------------- | ------------------------------- |
| 길이     | `size()`                | `s.size()`                      |
| 인덱스 접근 | `[]`, `at()`            | `s[0]`, `s.at(1)`               |
| 부분 문자열 | `substr()`              | `s.substr(2,3)`                 |
| 비교     | `==`, `compare()`       | `s1 == s2`                      |
| 연결     | `+`, `append()`         | `s1 + s2`, `s.append()`         |
| 삽입     | `insert()`              | `s.insert(0,"Hi")`              |
| 삭제     | `erase()`               | `s.erase(3,2)`                  |
| 교체     | `replace()`             | `s.replace(2,3,"xyz")`          |
| 찾기     | `find()`, `rfind()`     | `s.find("ab")`                  |
| 대문자    | `transform`             | `toupper()`                     |
| 소문자    | `transform`             | `tolower()`                     |
| 분리     | `stringstream`          | `split()` 직접 구현                 |
| 변환     | `stoi()`, `to_string()` | 문자열 ↔ 숫자                        |
| 트림     | 사용자 정의                  | `trim()`                        |
| 정렬     | `sort()`                | `std::sort(s.begin(), s.end())` |

---

# C++ 문자열 역방향 접근

## 1. `length()` 또는 `size()` 이용

```cpp
std::string str = "Hello";
char last = str[str.length() - 1]; // 또는 str[str.size() - 1]
```

* 문자열의 마지막 문자는 `length() - 1` 인덱스로 접근
* 빈 문자열일 경우 런타임 에러가 발생할 수 있음

```cpp
if (!str.empty()) {
    std::cout << str[str.size() - 1];
}
```

---

## 2. `.back()` 함수 (C++11 이상)

```cpp
std::string str = "Hello";
char last = str.back();  // 'o'
```

* 가장 직관적이고 가독성이 좋은 방법
* 단, 빈 문자열에서 호출하면 **정의되지 않은 동작** 발생

```cpp
if (!str.empty())
    std::cout << str.back();
```

---

## 3. `rbegin()` / `rend()` (역방향 반복자)

```cpp
std::string str = "Hello";
std::cout << *str.rbegin(); // 'o'
```

* 반복자 기반 코드에서 역순 접근 시 사용
* 뒤에서 앞으로 순회할 수 있음

```cpp
for (auto it = str.rbegin(); it != str.rend(); ++it)
    std::cout << *it; // 역순 출력
```

---

## 4. `substr()`을 이용한 뒤쪽 부분 문자열 추출

```cpp
std::string str = "HelloWorld";
std::string tail = str.substr(str.length() - 5); // "World"
```

* `substr(pos, len)`

  * `pos`: 시작 인덱스
  * `len`: 가져올 길이 (생략 시 끝까지)
* `length()`를 이용해 뒤에서부터 특정 부분만 잘라낼 수 있음

---

## 5. `find_last_of()`를 이용한 뒤쪽 검색

```cpp
std::string str = "apple.orange.banana";
size_t pos = str.find_last_of('.');
std::string ext = str.substr(pos + 1); // "banana"
```

* 특정 구분자 뒤의 문자열을 추출할 때 사용
* 구분자가 존재하지 않을 경우 `pos == std::string::npos` 검사 필요

---

## 6. `std::string_view` (C++17 이상)

```cpp
std::string_view sv = "HelloWorld";
auto tail = sv.substr(sv.size() - 3); // "rld"
```

* 복사 없이 부분 문자열을 참조할 수 있음
* `length()`와 `substr()` 사용 방식 동일
* 단, 원본 문자열이 소멸하면 참조가 무효화됨

---

## 요약표

| 방법                    | 설명           | 주의사항               |
| --------------------- | ------------ | ------------------ |
| `str[str.size() - 1]` | 기본적인 끝 문자 접근 | 빈 문자열 체크 필요        |
| `str.back()`          | 가장 직관적이고 깔끔  | 빈 문자열 예외 발생        |
| `str.rbegin()`        | 반복자 기반 역순 접근 | 코드가 약간 복잡함         |
| `str.substr(len - n)` | 뒤쪽 n글자 추출    | 인덱스 계산 필요          |
| `find_last_of()`      | 구분자 뒤 추출     | 구분자 없을 경우 예외 처리 필요 |
| `string_view`         | 복사 없는 부분 접근  | 원본 수명 관리 필요        |

---

## C 스타일 문자열(`char[]`) 비교

```cpp
#include <cstring>

char a[] = "apple";
char b[] = "banana";

strcmp(a, b);    // <0, =0, >0 반환
strcpy(dest, src);
strcat(dest, src);
strlen(a);
```

---

## C 문자열 <-> std::string 변환

```cpp
std::string s = "apple";
const char* cstr = s.c_str();  // C 스타일 문자열로 변환

char cstr2[] = "banana";
std::string s2 = cstr2;        // std::string으로 변환
```

