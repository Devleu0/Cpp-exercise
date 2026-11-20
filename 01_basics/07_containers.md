# 컨테이너

**컨테이너(container)** 는 여러 데이터를 저장하고 관리하기 위한 자료구조
**순서형**, **비순서형**, **연관형**, **Container Adaptor**로 나뉨

---

## **Sequence Containers**

 순서형 컨테이너, 데이터가 순서대로 저장되며, 인덱스나 반복자로 접근

| 컨테이너 | 설명   |
| ----------------- | ----------------------------------------- |
| `vector<T>`       | 동적 배열, 인덱스 접근 O, 끝 삽입/삭제 빠름               |
| `deque<T>`        | 양쪽 끝 삽입/삭제 O, 인덱스 접근 O                    |
| `list<T>`         | 이중 연결 리스트, 임의 접근 불가, 삽입/삭제 빠름             |
| `forward_list<T>` | 단일 연결 리스트, 메모리 절약                         |
| `array<T, N>`     | 정적 배열, 크기 고정, STL 알고리즘 사용 가능              |
| `string`          | 문자 컨테이너, 사실 `basic_string<char>`의 typedef |



```cpp
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <string>

vector<int> v = {1, 2, 3};
list<int> l = {1, 2, 3};
deque<int> dq = {1, 2, 3};
array<int, 3> arr = {1, 2, 3};
string s = "Hello";
```
## `std::vector` 주요 멤버 함수 정리

###  접근 

#### `at(size_t index)`

* 지정한 인덱스의 원소를 반환
* **범위 검사를 수행**하므로, 잘못된 인덱스에 접근하면 `std::out_of_range` 예외 발생
* 안전하지만 `operator[]`보다 약간 느림

```cpp
std::vector<int> v = {10, 20, 30};
std::cout << v.at(1);  // 출력: 20
```

---

#### `operator[](size_t index)`

* 인덱스를 통해 원소에 접근
* **범위 검사를 하지 않으므로**, 잘못된 인덱스 접근 시 **정의되지 않은 동작(UB)** 발생
* 빠르지만 주의해서 사용

```cpp
v[2] = 40;  // 정상
v[5] = 99;  //  잘못된 접근, UB 발생 가능
```

---

#### `front()`

* 벡터의 **첫 번째 원소에 대한 참조**를 반환
* 벡터가 비어 있으면 접근해서는 안 됨

```cpp
std::cout << v.front();  // 첫 번째 원소 출력
```

---

####  `back()`

* 벡터의 **마지막 원소에 대한 참조** 반환
* 역시 벡터가 비어 있으면 호출하면 안 됨

```cpp
std::cout << v.back();   // 마지막 원소 출력
```

---

####  `data()`

* 벡터가 내부적으로 사용하는 **연속된 메모리 블록의 첫 번째 주소** 반환
* `T*` 형태의 포인터를 얻을 수 있으며, C API와 호환할 때 유용

```cpp
int* p = v.data();
std::cout << *(p + 1);   // 두 번째 원소 접근
```

---

### 삽입 / 삭제

####  `push_back(const T& value)`

* 벡터의 **끝에 새로운 원소를 추가**
* 평균적으로 O(1)이지만, 내부 용량(capacity)을 초과할 경우 **재할당**이 발생

```cpp
v.push_back(50);
```

---

####  `pop_back()`

* **마지막 원소를 제거**
* 반환값은 없습니다. 즉, 제거된 값을 얻으려면 `back()`으로 미리 읽어야
* 비어 있는 벡터에서 호출하면 정의되지 않은 동작 발생

```cpp
int last = v.back();
v.pop_back();  // 마지막 원소 제거
```

---

####  `insert(iterator pos, const T& value)`

* 지정한 위치에 새 원소를 **삽입**
* 삽입 지점 뒤의 모든 원소가 한 칸씩 뒤로 밀리므로 **O(n)** 연산
* 삽입 시 기존의 반복자(iterator)와 포인터가 무효화

```cpp
v.insert(v.begin() + 1, 99);  // 두 번째 위치에 99 삽입
```

---

####  `erase(iterator pos)`

* 지정한 위치의 원소를 **삭제**
* 삭제된 뒤의 원소들이 앞으로 한 칸씩 이동하므로 **O(n)**
* 범위를 지정하여 여러 개를 한꺼번에 지울 수도 있습니다.

```cpp
v.erase(v.begin() + 2);            // 한 원소 삭제
v.erase(v.begin(), v.begin() + 3); // 구간 삭제
```

---

#### `emplace(iterator pos, Args&&... args)`

* 지정된 위치에 **객체를 직접 생성**
* `insert()`는 복사나 이동이 필요한 반면, `emplace()`는 생성자 인자를 그대로 전달하므로 더 효율적

```cpp
v.emplace(v.begin(), 10);  // 첫 위치에 직접 생성
```

---

#### `emplace_back(Args&&... args)`

* 벡터의 끝에 **객체를 직접 생성**
* `push_back()`과 비슷하지만, 불필요한 복사/이동이 생략
* 일반적으로 객체를 생성할 때 더 빠름

```cpp
v.emplace_back(42);
```

---

####  `clear()`

* 모든 원소를 제거하지만, **capacity(할당된 메모리)는 그대로 유지**
* 즉, 다음 삽입 시 재할당 없이 빠르게 사용 가능

```cpp
v.clear();  // 모든 원소 제거
```

---

* `at()` : 안전한 인덱스 접근 (범위 검사 O)
* `operator[]` : 빠른 접근, 검사 없음
* `front()`, `back()` : 앞뒤 원소 접근
* `data()` : 내부 배열 포인터 획득
* `push_back()` : 끝 삽입 (평균 O(1))
* `pop_back()` : 끝 삭제 (반환값 없음)
* `insert()` / `erase()` : 임의 위치 삽입 및 삭제 (O(n))
* `emplace()` / `emplace_back()` : 직접 생성 방식 삽입 (복사 생략)
* `clear()` : 모든 원소 제거 (capacity 유지)

---

| 컨테이너   | 주요 특징     | 접근 관련 함수 | 삽입/삭제 관련 함수| 용량 관련 함수    | 기타 함수  |
| ----------------------------------- | -------------------------------- | -------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **`vector<T>`**                     | 동적 배열, 인덱스 접근 `O(1)`, 끝 삽입/삭제 빠름 | `at()`, `operator[]`, `front()`, `back()`, `data()`            | `push_back()`, `pop_back()`, `insert()`, `erase()`, `emplace()`, `emplace_back()`, `clear()`                                                                                                                           | `size()`, `capacity()`, `empty()`, `resize()`, `reserve()`, `shrink_to_fit()` | `assign()`, `swap()`                                                                 |
| **`deque<T>`**                      | 양쪽 끝 삽입/삭제 `O(1)`, 인덱스 접근 가능     | `at()`, `operator[]`, `front()`, `back()`                      | `push_front()`, `push_back()`, `pop_front()`, `pop_back()`, `insert()`, `erase()`, `emplace_front()`, `emplace_back()`, `clear()`                                                                                      | `size()`, `empty()`, `resize()`, `shrink_to_fit()`                            | `assign()`, `swap()`     |
| **`list<T>`**                       | 이중 연결 리스트, 임의 접근 불가              | `front()`, `back()`                                            | `push_front()`, `push_back()`, `pop_front()`, `pop_back()`, `insert()`, `erase()`, `emplace_front()`, `emplace_back()`, `remove()`, `remove_if()`, `unique()`, `splice()`, `merge()`, `sort()`, `reverse()`, `clear()` | `size()`, `empty()` | `assign()`, `swap()` |
| **`forward_list<T>`**               | 단일 연결 리스트, 메모리 절약                | `front()`                                                      | `push_front()`, `pop_front()`, `insert_after()`, `erase_after()`, `emplace_front()`, `remove()`, `remove_if()`, `unique()`, `merge()`, `sort()`, `reverse()`, `clear()`                            | `empty()` (※ `size()` 없음)  | `assign()`, `swap()`  |
| **`array<T, N>`**                   | 정적 배열, 크기 고정, STL 알고리즘 사용 가능     | `at()`, `operator[]`, `front()`, `back()`, `data()`            | (삽입/삭제 불가, 크기 고정) | `size()`, `max_size()`, `empty()`    | `fill()`, `swap()`        |
| **`string`** (`basic_string<char>`) | 문자 전용 컨테이너, `vector<char>`와 유사   | `at()`, `operator[]`, `front()`, `back()`, `data()`, `c_str()` | `append()`, `push_back()`, `pop_back()`, `insert()`, `erase()`, `replace()`, `clear()`                                                                                                                                 | `size()`, `capacity()`, `resize()`, `reserve()`, `shrink_to_fit()`, `empty()` | `substr()`, `find()`, `rfind()`, `compare()`, `starts_with()`, `ends_with()`, `find_first_of()`, `find_last_of()`, `find_first_not_of()`, `find_last_not_of()`, `copy()`, `swap()` |


---

## **Associative Containers**

 연관형 컨테이너, 데이터를 자동으로 정렬해서 저장하며, 키 기반 검색이 빠름

| 컨테이너  | 설명     |
| ------------------ | ----------------- |
| `set<T>`           | 중복 없는 정렬된 값 저장    |
| `multiset<T>`      | 중복 허용, 정렬된 값 저장   |
| `map<Key, T>`      | 키-값 쌍 저장, 키는 유일   |
| `multimap<Key, T>` | 키-값 쌍 저장, 키 중복 허용 |



```cpp
#include <set>
#include <map>

set<int> s = {3, 1, 2}; // 자동 정렬: 1, 2, 3
map<string, int> m;
m["apple"] = 3;
m["banana"] = 5;
```

| 컨테이너                   | 주요 특징                 | 원소 접근 관련 함수                                                                          | 삽입/삭제 관련 함수                                             | 탐색 관련 함수                                                               | 용량 관련 함수                          | 기타 함수                        |
| ---------------------- | --------------------- | ------------------------------------------------------------------------------------ | ------------------------------------------------------- | ---------------------------------------------------------------------- | --------------------------------- | ---------------------------- |
| **`set<T>`**           | 정렬된 유일 원소 저장 (`<` 기준) | `begin()`, `end()`, `rbegin()`, `rend()`, `cbegin()`, `cend()`                       | `insert()`, `emplace()`, `erase()`, `clear()`, `swap()` | `find()`, `count()`, `lower_bound()`, `upper_bound()`, `equal_range()` | `size()`, `empty()`, `max_size()` | `key_comp()`, `value_comp()` |
| **`multiset<T>`**      | 정렬된 중복 원소 저장          | `begin()`, `end()`, `rbegin()`, `rend()`, `cbegin()`, `cend()`                       | `insert()`, `emplace()`, `erase()`, `clear()`, `swap()` | `find()`, `count()`, `lower_bound()`, `upper_bound()`, `equal_range()` | `size()`, `empty()`, `max_size()` | `key_comp()`, `value_comp()` |
| **`map<Key, T>`**      | `Key`는 유일, 정렬된 키-값 쌍  | `begin()`, `end()`, `rbegin()`, `rend()`, `cbegin()`, `cend()`, `at()`, `operator[]` | `insert()`, `emplace()`, `erase()`, `clear()`, `swap()` | `find()`, `count()`, `lower_bound()`, `upper_bound()`, `equal_range()` | `size()`, `empty()`, `max_size()` | `key_comp()`, `value_comp()` |
| **`multimap<Key, T>`** | 중복된 키 허용, 정렬된 키-값 쌍   | `begin()`, `end()`, `rbegin()`, `rend()`, `cbegin()`, `cend()`                       | `insert()`, `emplace()`, `erase()`, `clear()`, `swap()` | `find()`, `count()`, `lower_bound()`, `upper_bound()`, `equal_range()` | `size()`, `empty()`, `max_size()` | `key_comp()`, `value_comp()` |


---

## **Unordered Containers**

 비순서형 컨테이너, 해시 테이블 기반 저장, 평균적으로 매우 빠른 검색 속도(O(1)).

| 컨테이너  | 설명   |
| ---------------------------- | ------------ |
| `unordered_set<T>`           | 중복 없는 해시 집합  |
| `unordered_multiset<T>`      | 중복 허용 해시 집합  |
| `unordered_map<Key, T>`      | 키-값 해시 맵     |
| `unordered_multimap<Key, T>` | 키 중복 허용 해시 맵 |

---

## **Container Adaptors**

기본 컨테이너를 감싸서 특정 자료구조처럼 동작하도록 함.

| 컨테이너 | 설명   |
| ------------------- | ------- |
| `stack<T>`          | LIFO 구조 |
| `queue<T>`          | FIFO 구조 |
| `priority_queue<T>` | 우선순위 큐  |



```cpp
#include <stack>
#include <queue>

stack<int> st;
st.push(1);
st.push(2);

queue<int> q;
q.push(1);
q.push(2);
```

---

### **Utility Containers**

C++ 표준 라이브러리에서 값 묶음이나 편의 구조 제공.

| 컨테이너             | 설명            |
| ---------------- | ------------- |
| `pair<T1, T2>`   | 두 값 묶음        |
| `tuple<Ts...>`   | 여러 값 묶음       |
| `optional<T>`    | 값이 있거나 없음을 표현 |
| `variant<Ts...>` | 여러 타입 중 하나 저장 |



```cpp
#include <utility>
#include <tuple>
#include <optional>
#include <variant>

pair<int, string> p = {1, "apple"};
tuple<int, double, string> t = {1, 3.14, "pi"};
optional<int> o = 42; // 값 있음
optional<int> o2;     // 값 없음
variant<int, string> v = "hello";
```

---

## **Iterator & Algorithm**

모든 컨테이너는 반복자(iterator)를 제공, 동일한 알고리즘을 적용 가능

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

vector<int> v = {3, 1, 2};
sort(v.begin(), v.end()); // {1, 2, 3}
```

---

## 요약

| 종류              | 컨테이너 예시 |
| ----------------- | ---------------------------------------------------------------------------- |
| Sequence          | `vector`, `deque`, `list`, `forward_list`, `array`, `string`                 |
| Associative       | `set`, `multiset`, `map`, `multimap`                                         |
| Unordered         | `unordered_set`, `unordered_multiset`, `unordered_map`, `unordered_multimap` |
| Container Adapter | `stack`, `queue`, `priority_queue`                                           |
| Utility           | `pair`, `tuple`, `optional`, `variant`                                       |

### 참고
* [cppreference.com - Containers](https://en.cppreference.com/w/cpp/container)
