# C++ STL 라이브러리 (코테용)

> 코테에서 자주 쓰는 STL 컨테이너 · 알고리즘 · 헤더 정리. Python 의 `collections` / `heapq` / `bisect` / `itertools` 가 C++ 에서 무엇인지 찾을 때 보는 노트.
> Python 버전: [Warming-Up-for-Python/02_ps_notes/04_libraries.md](https://github.com/Devleu0/Warming-Up-for-Python/blob/main/02_ps_notes/04_libraries.md)

## 한눈에 보기 (Python → C++)

| Python | C++ | 헤더 | 비고 |
| --- | --- | --- | --- |
| `list` | `std::vector` | `<vector>` | |
| `collections.deque` | `std::deque` | `<deque>` | `push_front` / `pop_front` O(1) |
| `list` 를 스택으로 | `std::stack` | `<stack>` | `top()` 후 `pop()` (pop 은 반환값 없음) |
| `deque` 를 큐로 | `std::queue` | `<queue>` | `front()` 후 `pop()` |
| `heapq` (최소 힙) | `std::priority_queue<T, std::vector<T>, std::greater<T>>` | `<queue>` | 기본 `priority_queue` 는 **최대 힙** |
| `set` | `std::unordered_set` / `std::set` | `<unordered_set>` / `<set>` | `set` 은 정렬 유지 + `lower_bound` 가능 |
| `dict` | `std::unordered_map` / `std::map` | `<unordered_map>` / `<map>` | `map` 은 키 정렬 순회 |
| `collections.Counter` | `std::map<T, int>` + `++cnt[x]` | `<map>` | 없는 키는 0 으로 자동 생성 |
| `collections.defaultdict(list)` | `std::map<K, std::vector<V>>` | `<map>` | `m[k].push_back(v)` |
| 정렬된 리스트 + `bisect.insort` | `std::multiset` | `<set>` | 중복 허용 정렬 집합 |
| `bisect_left` / `bisect_right` | `std::lower_bound` / `std::upper_bound` | `<algorithm>` | [lower_upper_bound.cpp](../03_algorithms/binary_search/lower_upper_bound.cpp) |
| `itertools.permutations` | `std::next_permutation` | `<algorithm>` | 먼저 정렬해야 모든 순열 |
| `itertools.combinations` | 비트마스크 / `next_permutation` + bool 배열 | | |
| `itertools.accumulate` | `std::partial_sum` | `<numeric>` | |
| `functools.lru_cache` | 메모이제이션 배열 / `std::map` | | |
| `functools.cmp_to_key` | `std::sort` 의 비교 람다 | `<algorithm>` | C++ 는 원래 비교 함수 방식 |
| `math.gcd`, `math.lcm` | `std::gcd`, `std::lcm` | `<numeric>` | C++17 |
| `math.inf` | `std::numeric_limits<T>::max()` | `<limits>` | 또는 `1e9`, `1e18` |
| `tuple` | `std::pair` / `std::tuple` | `<utility>` / `<tuple>` | 사전식 비교 지원 |

---

## 1. 주요 STL 컨테이너

| 컨테이너             | 특징                 | 시간복잡도(평균)                         | 주요 메서드 / 패턴                                      |
| ---------------- | ------------------ | --------------------------------- | ------------------------------------------------ |
| `vector`         | 동적 배열, 임의 접근 O(1)  | push_back O(1), insert/erase O(N) | `v.push_back(x)`, `v[i]`, `v.begin()`, `v.end()` |
| `deque`          | 양쪽에서 push/pop 가능   | 양끝 삽입/삭제 O(1)                     | `push_front()`, `push_back()`, `pop_front()`     |
| `list`           | 양방향 연결 리스트         | 삽입/삭제 O(1), 접근 O(N)               | `insert(it, x)`, `erase(it)`                     |
| `stack`          | LIFO 구조            | push/pop O(1)                     | `push(x)`, `top()`, `pop()`                      |
| `queue`          | FIFO 구조            | push/pop O(1)                     | `push(x)`, `front()`, `pop()`                    |
| `priority_queue` | 최대/최소 힙            | 삽입/삭제 O(logN)                     | `push(x)`, `top()`, `pop()`                      |
| `set`            | 중복 없는 정렬된 자료       | 삽입/탐색/삭제 O(logN)                  | `insert(x)`, `find(x)`, `erase(x)`               |
| `unordered_set`  | 해시 기반 중복 없음        | 평균 O(1)                           | `insert(x)`, `find(x)`                           |
| `map`            | (key, value) 정렬 저장 | O(logN)                           | `m[key]`, `find(key)`, `erase(key)`              |
| `unordered_map`  | 해시 기반 (key, value) | 평균 O(1)                           | `m[key]`, `count(key)`                           |
| `pair`           | 두 값 묶음             | O(1)                              | `p.first`, `p.second`, `make_pair(a,b)`          |
| `tuple`          | 여러 값 묶음            | O(1)                              | `tie(a,b,c) = t;`, `get<0>(t)`                   |

---

## 2. 알고리즘 헤더 `<algorithm>`

| 함수                               | 기능                |                                                         |
| -------------------------------- | ----------------- | --------------------------------------------------------- |
| `sort(begin, end)`               | 오름차순 정렬           | `sort(v.begin(), v.end());`                               |
| `sort(begin, end, greater<>() )` | 내림차순 정렬           | `sort(v.begin(), v.end(), greater<int>());`               |
| `reverse(begin, end)`            | 순서 반전             | `reverse(v.begin(), v.end());`                            |
| `max_element(begin, end)`        | 최댓값 iterator 반환   | `*max_element(v.begin(), v.end())`                        |
| `min_element(begin, end)`        | 최솟값 iterator 반환   | `*min_element(v.begin(), v.end())`                        |
| `accumulate(begin, end, init)`   | 합계 (`<numeric>`)  | `accumulate(v.begin(), v.end(), 0)`                       |
| `count(begin, end, val)`         | 특정 값 개수           | `count(v.begin(), v.end(), 3)`                            |
| `find(begin, end, val)`          | 값 찾기              | `auto it = find(v.begin(), v.end(), x)`                   |
| `lower_bound(begin, end, x)`     | x 이상 첫 위치 (이진 탐색) | `auto it = lower_bound(v.begin(), v.end(), x)`            |
| `upper_bound(begin, end, x)`     | x 초과 첫 위치         | `auto it = upper_bound(v.begin(), v.end(), x)`            |
| `binary_search(begin, end, x)`   | 존재 여부             | `binary_search(v.begin(), v.end(), x)`                    |
| `unique(begin, end)`             | 연속 중복 제거          | `v.erase(unique(v.begin(), v.end()), v.end())`            |
| `next_permutation(begin, end)`   | 다음 순열 생성          | `do { ... } while(next_permutation(v.begin(), v.end()));` |

---

## 3. 문자열 관련 STL (`<string>`, `<sstream>`)

| 함수                 | 설명          |                          |
| ------------------ | ----------- | -------------------------- |
| `substr(pos, len)` | 부분 문자열      | `s.substr(2, 3)`           |
| `find(sub)`        | 부분 문자열 위치   | `s.find("abc")`            |
| `find_last_of()`   | 뒤에서부터 찾기    | `s.find_last_of('.')`      |
| `compare(str)`     | 문자열 비교      | `if (s1.compare(s2) == 0)` |
| `stoi()`, `stod()` | 문자열 → 숫자    | `stoi("123")`              |
| `to_string()`      | 숫자 → 문자열    | `to_string(42)`            |
| `stringstream`     | 공백 단위 split | `while (ss >> token)`      |

---

## 4. 그래프

그래프 표현 방법과 BFS / DFS / 격자 BFS / Dijkstra / Kruskal / 위상 정렬 템플릿은 [그래프 패턴](./05_graph_patterns.md) 노트로 옮겼습니다.

---

## 5. 자주 쓰는 조합

> 우선순위 큐 · 이진 탐색 · 중복 제거처럼 한 줄로 끝나는 관용구.

### 1) 우선순위 큐 (최소 힙)

```cpp
#include <queue>
priority_queue<int, vector<int>, greater<int>> pq;
pq.push(3);
pq.push(1);
pq.push(2);
cout << pq.top(); // 1
```

### 2) pair/vector 정렬

```cpp
vector<pair<int,int>> v;
sort(v.begin(), v.end(), [](auto &a, auto &b){
    if (a.first == b.first) return a.second < b.second;
    return a.first < b.first;
});
```

### 3) set으로 중복 제거

```cpp
set<int> s(v.begin(), v.end());
v.assign(s.begin(), s.end());
```

### 4) 이진 탐색으로 인덱스 찾기

```cpp
int idx = lower_bound(v.begin(), v.end(), x) - v.begin();
```

### 5) 문자열 split

```cpp
#include <sstream>
string s = "apple orange banana";
stringstream ss(s);
string token;
vector<string> res;
while (ss >> token) res.push_back(token);
```

---

## 기타 자주 쓰는 헤더

| 헤더                                   | 주요 기능                                 |
| ------------------------------------ | ------------------------------------- |
| `<numeric>`                          | `accumulate`, `partial_sum`           |
| `<cmath>`                            | `abs`, `pow`, `sqrt`, `ceil`, `floor` |
| `<climits>`                          | `INT_MAX`, `LLONG_MIN`                |
| `<queue>`                            | `queue`, `priority_queue`             |
| `<stack>`                            | `stack`                               |
| `<set>`, `<map>`                     | 균형 이진 트리 기반 컨테이너                      |
| `<unordered_set>`, `<unordered_map>` | 해시 기반 컨테이너                            |
| `<tuple>`                            | 다중 값 저장 (`tie`, `get<N>()`)           |
| `<bitset>`                           | 비트 단위 연산                              |

---

## 문제 해결용 STL

| 순위 | 이름                           | 용도           |
| -- | ---------------------------- | ------------ |
| 1  | `vector`                     | 배열, 인접 리스트   |
| 2  | `queue`                      | BFS 탐색       |
| 3  | `priority_queue`             | 다익스트라, 힙     |
| 4  | `pair`, `tuple`              | 좌표, 간선 저장    |
| 5  | `set` / `unordered_set`      | 방문 기록, 중복 제거 |
| 6  | `map` / `unordered_map`      | 키-값 매핑, 카운팅  |
| 7  | `stack`                      | DFS, 괄호검사    |
| 8  | `sort`, `lower_bound`,`upper_bound`        | 정렬 + 탐색      |
| 9  | `iota`, `find`, `accumulate` | 수열 처리        |
| 10 | `memset`, `fill`             | 초기화          |


---

## 사용 팁

| 상황           | 추천 STL / 패턴                                       |
| ------------ | ------------------------------------------------- |
| 그래프 탐색       | `vector<vector<int>>`, `queue`, `stack`           |
| 가중치 그래프      | `vector<vector<pair<int,int>>>`, `priority_queue` |
| 최소 스패닝 트리    | `vector<tuple<int,int,int>>`, `sort`              |
| 중복 없는 정렬 집합  | `set`, `unordered_set`                            |
| 빠른 탐색 (hash) | `unordered_map`, `unordered_set`                  |
| 문자열 분리       | `stringstream`, `find`, `substr`                  |
| 누적합          | `accumulate`, `partial_sum`                       |
| 순열 / 조합      | `next_permutation`, `bitmask`                     |
| 좌표 압축        | `sort`, `unique`, `lower_bound`                   |
| 입력 크기 고정, 빠른 접근 | `vector`                               |
| 삽입/삭제가 잦음       | `deque`, `list`                        |
| 정렬 필요, 중복 없음    | `set`, `map`                           |
| 중복 허용           | `multiset`, `multimap`                 |
| 빠른 탐색 (hash)    | `unordered_map`, `unordered_set`       |
| 최소/최대 우선순위      | `priority_queue`                       |
---
