# C++ STL 알고리즘 치트시트 (코테용)

> Python 내장함수에 대응하는 `<algorithm>` · `<numeric>` 함수 모음. 직접 짜기 전에 먼저 여기서 표준 함수가 있는지 확인하자.
> Python 버전: [Warming-Up-for-Python/02_ps_notes/02_builtins.md](https://github.com/Devleu0/Warming-Up-for-Python/blob/main/02_ps_notes/02_builtins.md)

## 한눈에 보기 (Python → C++)

| 하고 싶은 것 | Python | C++ | 헤더 |
| --- | --- | --- | --- |
| 인덱스 + 값 순회 | `for i, x in enumerate(v)` | `for (int i = 0; i < (int)v.size(); ++i)` | |
| 값만 순회 | `for x in v` | `for (int x : v)` / 수정하려면 `for (auto& x : v)` | |
| 합 | `sum(v)` | `std::accumulate(v.begin(), v.end(), 0LL)` | `<numeric>` |
| 최대 / 최소 | `max(v)`, `min(v)` | `*std::max_element(...)`, `*std::min_element(...)` | `<algorithm>` |
| 두 값 중 큰 값 | `max(a, b)` | `std::max(a, b)` (타입이 같아야 함) | `<algorithm>` |
| 여러 값 중 최대 | `max(a, b, c)` | `std::max({a, b, c})` | `<algorithm>` |
| 하나라도 / 모두 | `any(...)`, `all(...)` | `std::any_of`, `std::all_of`, `std::none_of` | `<algorithm>` |
| 개수 세기 | `v.count(x)` | `std::count(v.begin(), v.end(), x)` | `<algorithm>` |
| 조건 개수 | `sum(1 for x in v if ...)` | `std::count_if(..., pred)` | `<algorithm>` |
| 찾기 | `v.index(x)` | `std::find(...) - v.begin()` (없으면 `v.size()`) | `<algorithm>` |
| 뒤집기 | `v[::-1]`, `reversed(v)` | `std::reverse(v.begin(), v.end())` (제자리) | `<algorithm>` |
| 정렬 | `sorted(v)`, `v.sort()` | `std::sort(v.begin(), v.end())` (제자리) | `<algorithm>` |
| 중복 제거 | `sorted(set(v))` | `sort` + `v.erase(std::unique(...), v.end())` | `<algorithm>` |
| 0..n-1 채우기 | `list(range(n))` | `std::iota(v.begin(), v.end(), 0)` | `<numeric>` |
| 누적 합 | `itertools.accumulate` | `std::partial_sum` | `<numeric>` |
| 순열 | `itertools.permutations` | `std::next_permutation` | `<algorithm>` |
| 몫과 나머지 | `divmod(a, b)` | `a / b`, `a % b` (음수 주의, §6) | |
| 거듭제곱 나머지 | `pow(a, b, mod)` | 직접 구현 ([lucas_theorem.cpp](../03_algorithms/math/lucas_theorem.cpp) 의 `power`) | |
| 최대공약수 | `math.gcd` | `std::gcd`, `std::lcm` (C++17) | `<numeric>` |
| 절댓값 | `abs(x)` | `std::abs(x)` | `<cstdlib>` / `<cmath>` |
| 문자 ↔ 아스키 | `ord('a')`, `chr(97)` | `int('a')`, `char(97)` (`'c' - 'a'` = 2) | |
| 진법 변환 | `int("101", 2)`, `bin(5)` | `std::stoi("101", nullptr, 2)`, `std::bitset<8>(5)` | `<string>`, `<bitset>` |
| 무한대 | `float('inf')` | `1e9` / `1e18` / `std::numeric_limits<int>::max()` | `<limits>` |
| 두 값 교환 | `a, b = b, a` | `std::swap(a, b)` | `<utility>` |

> C++ 알고리즘은 대부분 **반복자 구간 `[begin, end)`** 를 받는다. `v.begin(), v.end()` 가 반복되는 게 번거로우면 C++20 의 `std::ranges::sort(v)` 를 쓸 수 있다.

---

## 1. 순회 — enumerate / zip 대응

```cpp
std::vector<char> v = {'a', 'b', 'c'};
for (int i = 0; i < (int)v.size(); ++i) std::cout << i << ' ' << v[i] << '\n';   // enumerate
for (int i = 0; i < (int)v.size(); ++i) std::cout << i + 1 << ' ' << v[i] << '\n';   // enumerate(v, 1)

std::vector<std::string> names = {"kim", "lee"};
std::vector<int> scores = {90, 80};
for (std::size_t i = 0; i < std::min(names.size(), scores.size()); ++i)   // zip (짧은 쪽 기준)
    std::cout << names[i] << ' ' << scores[i] << '\n';

std::map<std::string, int> d;                                             // dict(zip(names, scores))
for (std::size_t i = 0; i < names.size(); ++i) d[names[i]] = scores[i];

for (const auto& [name, score] : d) std::cout << name << ' ' << score << '\n';   // 구조화된 바인딩 (C++17)
```

## 2. map / filter / 컴프리헨션 대응

```cpp
#include <algorithm>
#include <numeric>

std::vector<int> nums = {1, 2, 3, 4};

std::vector<int> squares(nums.size());                       // [x * x for x in nums]
std::transform(nums.begin(), nums.end(), squares.begin(), [](int x) { return x * x; });

std::vector<int> evens;                                      // [x for x in nums if x % 2 == 0]
std::copy_if(nums.begin(), nums.end(), std::back_inserter(evens), [](int x) { return x % 2 == 0; });

// 사실 PS 에서는 그냥 for 문이 가장 읽기 쉽다
std::vector<int> evens2;
for (int x : nums) if (x % 2 == 0) evens2.push_back(x);
```

## 3. any / all / none

```cpp
std::vector<int> v = {1, 2, 3};
bool has_big = std::any_of(v.begin(), v.end(), [](int x) { return x > 2; });   // true
bool all_pos = std::all_of(v.begin(), v.end(), [](int x) { return x > 0; });   // true
bool no_neg  = std::none_of(v.begin(), v.end(), [](int x) { return x < 0; });  // true
// 빈 구간: any_of → false, all_of → true (Python 과 동일)
```

## 4. sum / max / min

```cpp
std::vector<int> v = {3, 1, 4};
long long total = std::accumulate(v.begin(), v.end(), 0LL);   // ⚠️ 초기값 타입이 결과 타입! 0 이면 int 로 계산됨
int mx = *std::max_element(v.begin(), v.end());               // 빈 벡터면 UB → 먼저 empty() 확인
int mx_idx = std::max_element(v.begin(), v.end()) - v.begin();   // 최댓값의 인덱스 (argmax)
auto [mn_it, mx_it] = std::minmax_element(v.begin(), v.end());

std::vector<std::string> words = {"apple", "fig", "banana"};   // max(words, key=len)
auto longest = *std::max_element(words.begin(), words.end(),
                                 [](const auto& a, const auto& b) { return a.size() < b.size(); });

std::max(1, 2LL);        // ❌ 컴파일 에러 (int vs long long) → std::max<long long>(1, 2LL)
```

## 5. 정렬 심화 — sort / stable_sort / 비교 함수

```cpp
std::vector<std::pair<int, char>> v = {{1, 'b'}, {2, 'a'}, {1, 'a'}};

std::sort(v.begin(), v.end());                        // pair 는 first → second 순 비교: (1,a) (1,b) (2,a)
std::sort(v.begin(), v.end(), std::greater<>());      // 내림차순
std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
    if (a.first != b.first) return a.first > b.first; // 숫자 내림차순
    return a.second < b.second;                       // 같으면 문자 오름차순
});
std::stable_sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
    return a.second < b.second;                       // 같은 키는 원래 순서 유지 (Python sort 와 같은 성질)
});

std::vector<std::string> words = {"banana", "kiwi", "apple"};
std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
    return std::make_pair(a.size(), a) < std::make_pair(b.size(), b);   // key=(len, 사전순)
});
```

* `std::sort` 는 **안정 정렬이 아니다**. 같은 키의 순서가 중요하면 `std::stable_sort`.
* 비교 함수는 반드시 `<` 의미(같으면 `false`)여야 한다 → [입출력과 함정 §4-10](./01_io_and_pitfalls.md#4-10-비교-함수는-strict-weak-ordering).
* 정렬 예제 코드: [sort_builtin.cpp](../03_algorithms/sorting/sort_builtin.cpp)

## 6. 정수 연산 함정

```cpp
std::cout << 7 / 2 << ' ' << -7 / 2 << '\n';    // 3 -3  ← 0 방향 버림 (Python: 3 -4)
std::cout << 7 % 3 << ' ' << -7 % 3 << '\n';    // 1 -1  ← Python: 1 2
std::cout << (a + b - 1) / b << '\n';           // 올림 나눗셈 (a, b > 0 일 때)
std::cout << std::round(2.5) << ' ' << std::round(3.5) << '\n';   // 3 4 ← 사사오입 (Python round 는 2 4)
std::cout << (1 << 31) << '\n';                 // ❌ int 오버플로 → 1LL << 31
```

* Python 의 `int` 는 무한 정밀도지만 C++ 는 `int`(±2.1×10⁹), `long long`(±9.2×10¹⁸) 범위를 넘으면 조용히 틀린다.
* 실수 비교는 `std::abs(a - b) < 1e-9`.

## 7. 구조화된 바인딩 / 부분 구간 / 삼항

```cpp
auto [q, r] = std::make_pair(7 / 2, 7 % 2);               // a, b = ...
std::pair<int, int> p = {1, 2};
auto [x, y] = p;
std::tuple<int, int, int> t = {1, 2, 3};
auto [a, b, c] = t;

std::vector<int> v = {0, 1, 2, 3, 4, 5};
std::vector<int> sub(v.begin() + 1, v.begin() + 4);       // v[1:4] → {1, 2, 3} (복사)
std::vector<int> rev(v.rbegin(), v.rend());               // v[::-1]
int last = v.back();                                      // v[-1]

std::string msg = (x % 2) ? "홀수" : "짝수";               // 삼항 연산자
if (1 <= x && x <= 10) {}                                 // ⚠️ 1 <= x <= 10 은 C++ 에서 의도대로 동작하지 않음
```

## 8. vector 자주 쓰는 멤버 함수

```cpp
std::vector<int> v = {3, 1, 2};
v.push_back(4);                  // 끝에 추가 O(1)   (append)
v.emplace_back(5);               // 생성자 인자로 바로 생성 (pair/tuple 에 유용)
v.insert(v.begin(), 9);          // 앞에 삽입 O(N)  → 자주 쓰면 deque
v.pop_back();                    // 끝 제거 O(1)     (반환값 없음! 먼저 v.back() 으로 읽기)
v.erase(v.begin());              // 앞 제거 O(N)
v.erase(v.begin() + 1, v.begin() + 3);   // 구간 삭제
v.insert(v.end(), {7, 8});       // extend
v.resize(10);                    // 크기 변경 (늘어난 칸은 0)
v.assign(5, -1);                 // 크기 5, 모두 -1 로 다시 채움
v.clear();                       // 비우기
v.reserve(1'000'000);            // 미리 용량 확보 (push_back 재할당 줄이기)
bool empty = v.empty();
```

* 전체 컨테이너 정리는 [01_basics/07_containers.md](../01_basics/07_containers.md).

## 9. 복사 vs 참조

```cpp
std::vector<int> a = {1, 2, 3};
std::vector<int> b = a;        // ✅ 깊은 복사 (Python 의 a[:] / deepcopy 와 같음)
std::vector<int>& c = a;       // 별칭 (Python 의 b = a)
b.push_back(4);                // a 는 그대로
c.push_back(5);                // a 도 바뀜

std::vector<std::vector<int>> g = {{1, 2}, {3, 4}};
auto h = g;                    // 2차원도 통째로 깊은 복사

void f(std::vector<int> v);          // 값 전달: 호출할 때마다 복사 (느림)
void f(const std::vector<int>& v);   // 읽기 전용 참조: 복사 없음 ← 기본으로 사용
void f(std::vector<int>& v);         // 수정 가능한 참조
```

## 10. 2차원 배열 초기화

```cpp
int n = 3, m = 4;
std::vector<std::vector<int>> grid(n, std::vector<int>(m, 0));   // ✅ 행마다 독립 (Python 의 [[0]*m]*n 문제 없음)
grid[0][0] = 1;

int arr[3][4] = {};                 // 고정 크기 배열 0 초기화
std::vector<std::string> board(n, std::string(m, '.'));          // 문자 격자
```

* 다양한 초기화 방법은 [01_basics/06_array_vector_init.md](../01_basics/06_array_vector_init.md).

## 11. for-else 대응

```cpp
bool found = false;
for (int x : {1, 3, 5}) {
    if (x % 2 == 0) { found = true; break; }
}
if (!found) std::cout << "짝수 없음\n";

// 또는 알고리즘 함수로
std::vector<int> v = {1, 3, 5};
if (std::none_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; })) std::cout << "짝수 없음\n";
```

## 12. 문자 판별 함수 (`<cctype>`)

```cpp
#include <cctype>
char c = 'a';
std::isalpha(c); std::isdigit(c); std::isalnum(c); std::isupper(c); std::islower(c); std::isspace(c);
char up = std::toupper(c);          // 'A'
int idx = c - 'a';                  // 0  (알파벳 인덱스)
char d = 'a' + 3;                   // 'd'
int digit = '7' - '0';              // 7  (문자 → 숫자)
```

* 문자열 전체 변환·분리·검색은 [문자열 다루기](./03_strings.md).
