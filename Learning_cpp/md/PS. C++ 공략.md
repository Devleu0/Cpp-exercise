# C++ Problem Solving 공략

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

## 4. 그래프 관련 STL 패턴

| 용도              | 자료구조                                                              |  코드                                                                    |
| --------------- | ----------------------------------------------------------------- | ------------------------------------------------------------------------ |
| 인접 리스트          | `vector<vector<int>>`                                             | `vector<vector<int>> graph(n+1); graph[u].push_back(v);`                 |
| 방문 체크           | `vector<bool>`                                                    | `vector<bool> visited(n+1, false);`                                      |
| 큐 BFS           | `queue<int>`                                                      | `queue<int> q; q.push(start);`                                           |
| DFS 재귀          | `vector<int>` + 재귀                                                | `dfs(node) { for (auto nxt : graph[node]) if(!visited[nxt]) dfs(nxt); }` |
| 가중치 그래프         | `vector<vector<pair<int,int>>>`                                   | `graph[u].push_back({v, w});`                                            |
| 최단경로 (Dijkstra) | `priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>>` | `pq.push({dist, node});`                                                 |
| 간선 리스트          | `vector<tuple<int,int,int>>`                                      | Kruskal: `(가중치, u, v)`                                                   |
| BFS 레벨          | `queue<pair<int,int>>`                                            | `q.push({node, depth});`                                                 |
| 방향 그래프          | `graph[u].push_back(v);`                                          | 단방향만 연결                                                                  |
| 무방향 그래프         | `graph[u].push_back(v); graph[v].push_back(u);`                   | 양방향 연결                                                                   |

---

<details> <summary>`1: BFS (너비 우선 탐색)`</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<bool> visited;

void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nxt : graph[cur]) {
            if (!visited[nxt]) {
                visited[nxt] = true;
                q.push(nxt);
            }
        }
    }
}
```
</details>

<details> <summary>`2: DFS (깊이 우선 탐색)`</summary>

```cpp
void dfs(int cur) {
    visited[cur] = true;
    for (int nxt : graph[cur]) {
        if (!visited[nxt])
            dfs(nxt);
    }
}
```
</details> 

<details><summary> `3: Dijkstra (최단 경로)`</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
vector<vector<pair<int,int>>> graph;
vector<int> dist;

void dijkstra(int start) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [cost, cur] = pq.top(); pq.pop();
        if (cost > dist[cur]) continue;

        for (auto [next, weight] : graph[cur]) {
            int newCost = cost + weight;
            if (newCost < dist[next]) {
                dist[next] = newCost;
                pq.push({newCost, next});
            }
        }
    }
}
```
</details>

<details><summary>`4: Kruskal (MST)`</summary>

```cpp
struct Edge { int w, u, v; };
vector<Edge> edges;
vector<int> parent;

int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a != b) parent[b] = a;
}

int kruskal(int n) {
    sort(edges.begin(), edges.end(), [](auto &a, auto &b){ return a.w < b.w; });
    parent.resize(n+1);
    iota(parent.begin(), parent.end(), 0);

    int total = 0;
    for (auto &e : edges) {
        if (find(e.u) != find(e.v)) {
            unite(e.u, e.v);
            total += e.w;
        }
    }
    return total;
}
```

</details>

---

## 5. 자주 쓰는 조합

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
