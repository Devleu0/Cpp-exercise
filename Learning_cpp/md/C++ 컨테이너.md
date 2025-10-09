# 컨테이너

**컨테이너(container)** 는 여러 데이터를 저장하고 관리하기 위한 자료구조
**순서형**, **비순서형**, **연관형**, **Container Adaptor**로 나뉨

---

### **Sequence Containers**

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

---

### **Associative Containers**

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

---

### **Unordered Containers**

 비순서형 컨테이너, 해시 테이블 기반 저장, 평균적으로 매우 빠른 검색 속도(O(1)).

| 컨테이너  | 설명   |
| ---------------------------- | ------------ |
| `unordered_set<T>`           | 중복 없는 해시 집합  |
| `unordered_multiset<T>`      | 중복 허용 해시 집합  |
| `unordered_map<Key, T>`      | 키-값 해시 맵     |
| `unordered_multimap<Key, T>` | 키 중복 허용 해시 맵 |

---

### **Container Adaptors**

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

### **Iterator & Algorithm**

모든 컨테이너는 반복자(iterator)를 제공, 동일한 알고리즘을 적용 가능

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

vector<int> v = {3, 1, 2};
sort(v.begin(), v.end()); // {1, 2, 3}
```

---

### 요약

| 종류              | 컨테이너 예시 |
| ----------------- | ---------------------------------------------------------------------------- |
| Sequence          | `vector`, `deque`, `list`, `forward_list`, `array`, `string`                 |
| Associative       | `set`, `multiset`, `map`, `multimap`                                         |
| Unordered         | `unordered_set`, `unordered_multiset`, `unordered_map`, `unordered_multimap` |
| Container Adapter | `stack`, `queue`, `priority_queue`                                           |
| Utility           | `pair`, `tuple`, `optional`, `variant`                                       |

### 참고
* [cppreference.com - Containers](https://en.cppreference.com/w/cpp/container)
