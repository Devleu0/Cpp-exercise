# C++ 배열 초기화 방식 정리

## 1. 기본 C 스타일 배열 초기화

```cpp
int arr[5] = {1, 2, 3, 4, 5};
```

* 크기 지정 + 초기값 나열
* 초기값 개수가 배열 크기보다 작으면 나머지는 0으로 자동 초기화됨

```cpp
int arr[5] = {1, 2}; // {1, 2, 0, 0, 0}
```

---

## 2. 크기 생략 초기화

```cpp
int arr[] = {1, 2, 3, 4, 5};
```

* 배열 크기를 컴파일러가 자동으로 계산

---

## 3. 전부 0으로 초기화

```cpp
int arr[5] = {0}; // 모든 요소가 0
int arr[5] = {};  // C++11 이후 가능 (모두 0)
```

* `{}`는 값 초기화(value initialization)로 동작함

---

## 4. C++11 이상 - Uniform Initialization (일관된 초기화)

```cpp
int arr[3]{1, 2, 3}; // C++11 이후
```

* `=` 생략 가능
* `()` 대신 `{}` 사용 권장 (narrowing conversion 방지)

---

## 5. 다차원 배열 초기화

```cpp
int matrix[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
```

* 내부 중괄호는 생략 가능하지만 명시하면 가독성이 좋음
* 초기값 부족 시 자동으로 0으로 채움

```cpp
int matrix[2][3] = { {1}, {4, 5} }; // {{1,0,0}, {4,5,0}}
```

---

## 6. `memset`으로 0 초기화 (비권장)

```cpp
int arr[5];
std::memset(arr, 0, sizeof(arr));
```

* 모든 바이트를 0으로 설정
* `int`, `char` 등 단순 타입에서는 안전하지만
  `double`, `struct` 등에서는 안전하지 않음

---

## 7. 동적 배열 초기화 (`new` 사용)

```cpp
int* arr = new int[5]{1, 2, 3, 4, 5}; // C++11 이후 가능
delete[] arr;
```

C++11 이전에는 직접 대입해야 했음:

```cpp
int* arr = new int[5];
for (int i = 0; i < 5; ++i) arr[i] = 0;
```

---

## 8. `std::array` 초기화 

```cpp
#include <array>

std::array<int, 3> arr = {1, 2, 3};
std::array<int, 3> arr2{4, 5, 6};
```

* 크기가 고정된 배열이지만 STL 컨테이너로 동작
* `.size()`, `.begin()`, `.end()` 등 사용 가능
* 성능은 일반 배열과 동일

---
# Vector
## 1. `std::vector` 초기화 

```cpp
#include <vector>

std::vector<int> v = {1, 2, 3, 4};  // C++11 이후
std::vector<int> v(5, 0);           // 5개의 0으로 초기화
```

* 런타임에 크기를 결정 가능
* 메모리를 자동으로 관리

---

## 2. 2차원 벡터 크기만 지정 
`vector<vector<int>> v(n, vector<int>(m));`
  → 2차원 크기만 지정하고, 내부 값은 기본값(0)으로 채움.
```cpp
#include <vector>
using namespace std;

int main() {
    int n = 3;  // 행
    int m = 4;  // 열

    // 3행 4열, 모든 원소가 0으로 초기화됨
    vector<vector<int>> v(n, vector<int>(m));

    // 나중에 값 대입 가능
    v[1][2] = 42;
}
```

값 초기화 생략 가능. 크기를 **나중에 동적으로 지정** 가능. 
메모리 초기화 비용을 **최소화**할 수 있음.
```cpp
#include <vector>
using namespace std;

int main() {
    int n = 3, m = 4;
    vector<vector<int>> v(n); // 일단 행만 n개 확보

    for (int i = 0; i < n; ++i) {
        v[i].resize(m); // 각 행마다 열 크기를 나중에 지정
    }
}
```

##  3. 3차원 이상 벡터 동적 크기 지정

```cpp
int x = 2, y = 3, z = 4;
ve능
```cpp
vector<vector<int>> v;
v.resize(5);           // 5행 생성
for (int i = 0; i < 5; ++i)
    v[i].resize(10);   // 각 행에 10열 생성
```


## 정리

| 종류            | 문법 예시                              | 특징               |
| ------------- | ---------------------------------- | ---------------- |
| 기본 배열         | `int a[5] = {1,2,3};`              | 남는 공간은 0         |
| 크기 생략         | `int a[] = {1,2,3};`               | 자동 크기 결정         |
| 전부 0          | `int a[5] = {};`                   | C++11 이후         |
| Uniform Init  | `int a[]{1,2,3};`                  | `=` 생략 가능        |
| 다차원 배열        | `int a[2][3] = {{1,2,3},{4,5,6}};` | 내부 중괄호 생략 가능     |
| `memset`      | `memset(a,0,sizeof(a));`           | 비권장, int만 안전     |
| `new` 배열      | `new int[5]{1,2,3};`               | 수동 할당, delete 필요 |
| `std::array`  | `std::array<int,3> a={1,2,3};`     | 고정 크기 컨테이너       |
| `std::vector` | `std::vector<int> v={1,2,3,4};`    | 가변 크기 컨테이너       |

---

