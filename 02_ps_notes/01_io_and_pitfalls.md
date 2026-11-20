# C++ 코테 입출력 & 흔한 함정

> 로직은 맞는데 틀리거나 시간 초과가 나는 대부분의 원인 모음.
> Python 버전: [Warming-Up-for-Python/02_ps_notes/01_io_and_pitfalls.md](https://github.com/Devleu0/Warming-Up-for-Python/blob/main/02_ps_notes/01_io_and_pitfalls.md)

## 1. 입력 패턴 모음

<!-- check:compile -->
```cpp
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);  // C 표준 입출력과 동기화 해제 → cin/cout 이 빨라짐
    std::cin.tie(nullptr);             // cin 할 때마다 cout 을 flush 하지 않음

    // 1) 정수 하나 / 여러 개 (공백·개행 구분 없이 읽힘)
    int n, m;
    std::cin >> n >> m;

    // 2) 정수 배열
    std::vector<int> arr(n);
    for (auto& x : arr) std::cin >> x;

    // 3) n × m 격자 (공백 구분 숫자)
    std::vector<std::vector<int>> grid(n, std::vector<int>(m));
    for (auto& row : grid)
        for (auto& x : row) std::cin >> x;

    // 4) n × m 격자 (붙어 있는 문자열: "0110")
    std::vector<std::string> board(n);
    for (auto& row : board) std::cin >> row;          // board[r][c] - '0' 으로 숫자 변환

    // 5) 공백이 포함된 한 줄
    std::cin.ignore();                                // 직전 >> 가 남긴 '\n' 제거 (필수!)
    std::string line;
    std::getline(std::cin, line);

    // 6) 입력 끝까지 읽기 (테스트케이스 수 미지정)
    int a, b;
    while (std::cin >> a >> b) { /* ... */ }
}
```

* `cin >> x` 는 **공백·탭·개행을 모두 건너뛴다** → 한 줄에 몇 개가 있든 상관없이 읽힌다.
* `>>` 다음에 `getline` 을 쓰면 남아 있던 개행 때문에 **빈 문자열**이 읽힌다 → `cin.ignore()` 또는 `std::cin >> std::ws`.
* `sync_with_stdio(false)` 이후에는 `scanf/printf` 와 `cin/cout` 을 **섞어 쓰면 안 된다** (출력 순서가 꼬임).

## 2. 출력 패턴 모음

```cpp
#include <iomanip>   // setprecision, setw, setfill

std::cout << a << ' ' << b << '\n';                       // 공백 구분
for (int x : arr) std::cout << x << ' ';                  // 1 2 3 (끝 공백은 대부분 채점기가 허용)
std::cout << (ok ? "YES" : "NO") << '\n';
std::cout << std::fixed << std::setprecision(2) << x;     // 3.14 (소수점 둘째 자리)
std::cout << std::setw(5) << std::setfill('0') << 42;     // 00042
```

* 자세한 형식 지정은 [출력 형식](./07_output_format.md) 노트 참고.

## 3. 시간 초과(TLE) 단골 원인

| 상황 | 느린 코드 | 개선 |
| --- | --- | --- |
| 입력이 많음 | 기본 `cin` | `sync_with_stdio(false)` + `cin.tie(nullptr)` |
| 출력이 많음 | `std::endl` 반복 (매번 flush) | `'\n'` 사용 |
| 앞에서 삭제/삽입 | `v.erase(v.begin())`, `v.insert(v.begin(), x)` O(N) | `std::deque` |
| 존재 여부 확인 반복 | `std::find(v.begin(), v.end(), x)` O(N) | `set` / `unordered_set` (O(log N) / O(1)) |
| 큰 객체를 함수에 전달 | `void f(std::vector<int> v)` (매번 복사) | `const std::vector<int>& v` |
| 문자열 누적 | `s = s + c` (매번 새 문자열) | `s += c` 또는 `s.push_back(c)` |
| 루프 안에서 컨테이너 생성 | `std::vector<int> tmp(n)` 를 반복 | 밖에서 한 번 만들고 `assign`/`clear` |
| `map` 남용 | 키 범위가 작은데 `std::map` | 배열 / `vector` 로 인덱싱 |

* C++ 는 대략 **1초에 1억 번** 단순 연산을 어림잡는다 (Python 은 약 1천만 번).
* `unordered_map` 은 평균 O(1) 이지만 해시 충돌을 노린 데이터에서는 느려질 수 있다 → 불안하면 `map`.

## 4. 흔한 버그 모음

### 4-1. 정수 오버플로

```cpp
int a = 100000, b = 100000;
long long bad = a * b;                     // ❌ int 끼리 곱해서 넘친 뒤에 long long 으로 변환
long long good = 1LL * a * b;              // ✅ 먼저 long long 으로
long long sum = 0;                         // 합은 처음부터 long long
const long long INF = 1e18;                // 거리 INF 도 long long
```

* `int` 는 약 ±21억(2.1 × 10⁹). 합·곱·거리는 습관적으로 `long long`.
* `INT_MAX + 1` 처럼 **INF 끼리 더하면** 넘친다 → INF 는 `1e9`(int) / `1e18`(long long) 처럼 여유 있게.

### 4-2. 나눗셈과 나머지 (Python 과 다름!)

```cpp
std::cout << 7 / 2 << ' ' << -7 / 2 << '\n';   // 3 -3   ← 0 방향으로 버림 (Python 은 -4)
std::cout << 7 % 3 << ' ' << -7 % 3 << '\n';   // 1 -1   ← 부호가 왼쪽을 따라감 (Python 은 2)
int r = ((a % m) + m) % m;                      // 항상 0 이상인 나머지
double d = 7 / 2;                               // 3.0 ← 정수 나눗셈 후 변환! 7.0 / 2 로 써야 3.5
```

### 4-3. 부호 없는 정수(size_t) 언더플로

```cpp
std::vector<int> v;                 // 비어 있음
for (int i = 0; i < v.size() - 1; ++i) {}   // ❌ v.size() - 1 이 0 - 1 = 18446744073709551615
for (int i = 0; i + 1 < (int)v.size(); ++i) {}   // ✅
```

### 4-4. 배열 범위 밖 접근 (Undefined Behavior)

```cpp
std::vector<int> v(5);
v[5] = 1;        // ❌ 에러 없이 조용히 메모리를 망가뜨림 (Python 은 IndexError)
v.at(5) = 1;     // 디버깅할 때는 at() → std::out_of_range 예외
```

* 로컬에서 `-fsanitize=address,undefined -D_GLIBCXX_DEBUG` 로 컴파일하면 바로 잡아준다.

### 4-5. 초기화하지 않은 지역 변수

```cpp
int cnt;            // ❌ 쓰레기 값 (전역 변수는 0 으로 초기화되지만 지역 변수는 아님)
int cnt2 = 0;       // ✅
int arr[100];       // ❌ 지역 배열도 마찬가지 → int arr[100] = {}; 또는 std::vector<int>(100)
```

### 4-6. 반복 중 컨테이너 수정

```cpp
std::vector<int> v = {1, 2, 3, 4};
for (auto it = v.begin(); it != v.end(); ) {
    if (*it % 2 == 0) it = v.erase(it);   // ✅ erase 가 돌려준 다음 반복자를 사용
    else ++it;
}
// 더 간단히 (erase-remove 관용구, C++20 은 std::erase_if)
v.erase(std::remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), v.end());
```

### 4-7. map 의 operator[] 는 원소를 만든다

```cpp
std::map<std::string, int> m;
if (m["kim"] == 0) {}         // ❌ "kim" 이 없으면 0 으로 삽입됨 → size 가 늘어남
if (m.count("kim")) {}        // ✅ 존재 여부만 확인 (C++20: m.contains("kim"))
if (auto it = m.find("kim"); it != m.end()) { /* it->second */ }
```

### 4-8. 실수 비교

```cpp
if (0.1 + 0.2 == 0.3) {}                    // ❌ false
if (std::abs((0.1 + 0.2) - 0.3) < 1e-9) {}  // ✅
int root = (int)std::sqrt(n);               // ❌ 큰 n 에서 오차 가능
while ((long long)root * root > n) --root;  // ✅ 정수로 보정
while ((long long)(root + 1) * (root + 1) <= n) ++root;
```

### 4-9. 재귀 깊이

* C++ 는 Python 처럼 재귀 제한(`setrecursionlimit`)은 없지만 **스택 메모리**(보통 1~8MB)가 한계다.
* 깊이 10⁵~10⁶ 의 DFS 는 스택 오버플로(Segmentation fault) 가능 → 반복문 + `std::stack` 으로 바꾸거나, 큰 배열은 전역/`vector` 로.

### 4-10. 비교 함수는 strict weak ordering

```cpp
std::sort(v.begin(), v.end(), [](int a, int b) { return a <= b; });   // ❌ 같을 때 true → 런타임 에러 가능
std::sort(v.begin(), v.end(), [](int a, int b) { return a < b; });    // ✅
```

## 5. 자주 쓰는 초기값

```cpp
const int INF = 1e9;                 // int 용
const long long LINF = 1e18;         // long long 용
std::vector<long long> dist(n + 1, LINF);
std::vector<bool> visited(n + 1, false);
std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));   // 2차원 (Python 같은 공유 문제 없음)

// 4방향 이동
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};
for (int dir = 0; dir < 4; ++dir) {
    int next_row = row + dr[dir], next_col = col + dc[dir];
    if (next_row < 0 || next_row >= n || next_col < 0 || next_col >= m) continue;   // 범위 체크
}

// 배열 채우기
std::fill(dist.begin(), dist.end(), LINF);
int arr[100]; std::fill(arr, arr + 100, -1);     // memset 은 0, -1 외의 값에 쓰면 안 됨
```

## 6. 코테 템플릿

<!-- check:compile -->
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (auto& x : arr) std::cin >> x;

    ll total = 0;
    for (int x : arr) total += x;
    std::cout << total << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tc = 1;
    // std::cin >> tc;      // 테스트케이스가 여러 개면 주석 해제
    while (tc--) solve();
}
```

* 대회에서는 `#include <bits/stdc++.h>` + `using namespace std;` 를 많이 쓴다. 빠르지만 **GCC 전용**이고 이름 충돌(`count`, `next` 등)이 생길 수 있다.
