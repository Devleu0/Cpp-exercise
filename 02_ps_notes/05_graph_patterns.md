# 그래프 패턴 템플릿

> 코테에서 바로 꺼내 쓰는 그래프 템플릿. 전체 구현과 예제 입출력은 [03_algorithms/graph](../03_algorithms/graph) 에 있다.
> Python 버전: [Warming-Up-for-Python/02_ps_notes/05_graph_patterns.md](https://github.com/Devleu0/Warming-Up-for-Python/blob/main/02_ps_notes/05_graph_patterns.md)

## 그래프 표현 방법

| 용도 | 자료구조 | 코드 |
| --- | --- | --- |
| 인접 리스트 | `std::vector<std::vector<int>>` | `graph[u].push_back(v);` |
| 가중치 그래프 | `std::vector<std::vector<std::pair<int, int>>>` | `graph[u].emplace_back(v, w);` |
| 무방향 그래프 | 양쪽 모두 추가 | `graph[u].push_back(v); graph[v].push_back(u);` |
| 인접 행렬 (N ≤ 수백) | `std::vector<std::vector<int>>(n, std::vector<int>(n, INF))` | `adj[u][v] = w;` |
| 간선 리스트 | `std::vector<std::tuple<int, int, int>>` | Kruskal: `(비용, u, v)` |
| 방문 체크 | `std::vector<bool>` | `std::vector<bool> visited(n + 1, false);` |

```cpp
int n, m;
std::cin >> n >> m;
std::vector<std::vector<int>> graph(n + 1);   // 노드 번호가 1부터면 n + 1
for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
}
```

## 1. BFS (너비 우선 탐색)

가중치 없는 그래프의 **최단 거리**.

```cpp
std::vector<int> bfs(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<int> dist(graph.size(), -1);   // -1 = 미방문
    std::queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int next : graph[cur]) {
            if (dist[next] != -1) continue;
            dist[next] = dist[cur] + 1;   // 넣을 때 방문 처리 → 중복 삽입 방지
            q.push(next);
        }
    }
    return dist;
}
```

## 2. DFS (깊이 우선 탐색)

```cpp
void dfs(const std::vector<std::vector<int>>& graph, int cur, std::vector<bool>& visited) {
    visited[cur] = true;
    for (int next : graph[cur]) {
        if (!visited[next]) dfs(graph, next, visited);
    }
}

// 깊이가 매우 깊을 수 있으면(10^5 이상) 스택으로
void dfs_iterative(const std::vector<std::vector<int>>& graph, int start, std::vector<bool>& visited) {
    std::stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int cur = st.top();
        st.pop();
        if (visited[cur]) continue;
        visited[cur] = true;
        for (int next : graph[cur]) {
            if (!visited[next]) st.push(next);
        }
    }
}
```

## 3. 격자(2차원) BFS

미로 최단 거리, 섬 개수 등. 예제: [connected_components.cpp](../03_algorithms/graph/connected_components.cpp)

```cpp
int grid_bfs(const std::vector<std::string>& board, int start_row, int start_col) {
    const int n = board.size(), m = board[0].size();
    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};

    std::vector<std::vector<int>> dist(n, std::vector<int>(m, -1));
    std::queue<std::pair<int, int>> q;
    dist[start_row][start_col] = 0;
    q.emplace(start_row, start_col);

    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();
        for (int dir = 0; dir < 4; ++dir) {
            int next_row = row + dr[dir], next_col = col + dc[dir];
            if (next_row < 0 || next_row >= n || next_col < 0 || next_col >= m) continue;
            if (board[next_row][next_col] == '#' || dist[next_row][next_col] != -1) continue;
            dist[next_row][next_col] = dist[row][col] + 1;
            q.emplace(next_row, next_col);
        }
    }
    return dist[n - 1][m - 1];   // 도착점까지 거리 (못 가면 -1)
}
```

## 4. Dijkstra (최단 경로)

음수 가중치가 없는 그래프. 예제: [dijkstra.cpp](../03_algorithms/graph/dijkstra.cpp)

```cpp
const long long INF = 1e18;

std::vector<long long> dijkstra(const std::vector<std::vector<std::pair<int, int>>>& graph, int start) {
    std::vector<long long> dist(graph.size(), INF);
    using Item = std::pair<long long, int>;                                  // (거리, 노드)
    std::priority_queue<Item, std::vector<Item>, std::greater<>> pq;        // 최소 힙
    dist[start] = 0;
    pq.emplace(0, start);
    while (!pq.empty()) {
        auto [d, cur] = pq.top();
        pq.pop();
        if (d > dist[cur]) continue;                                         // 오래된 항목 건너뛰기
        for (auto [next, w] : graph[cur]) {
            if (dist[cur] + w < dist[next]) {
                dist[next] = dist[cur] + w;
                pq.emplace(dist[next], next);
            }
        }
    }
    return dist;
}
```

* `std::priority_queue` 는 기본이 **최대 힙**. `std::greater<>` 를 넣어야 최소 힙이 된다 (Python `heapq` 는 최소 힙).
* 최대 힙을 쓰면서 부호를 뒤집는 방법(`pq.push({-d, node})`)도 자주 보인다.

## 5. Kruskal (MST)

예제: [mst.cpp](../03_algorithms/graph/mst.cpp), Union-Find: [disjoint_set.cpp](../03_algorithms/data_structure/disjoint_set.cpp)

```cpp
std::vector<int> parent;

int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }

bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;   // 이미 같은 집합 → 사이클
    parent[b] = a;
    return true;
}

long long kruskal(int n, std::vector<std::tuple<int, int, int>> edges) {   // (비용, u, v)
    std::sort(edges.begin(), edges.end());
    parent.resize(n + 1);
    std::iota(parent.begin(), parent.end(), 0);
    long long total = 0;
    for (auto [cost, u, v] : edges) {
        if (unite(u, v)) total += cost;
    }
    return total;
}
```

## 6. 위상 정렬 (Kahn)

선후 관계가 있는 작업 순서. 예제: [topological_sort.cpp](../03_algorithms/graph/topological_sort.cpp)

```cpp
std::vector<int> topo_sort(const std::vector<std::vector<int>>& graph, int n) {
    std::vector<int> indegree(n + 1, 0), order;
    for (int u = 1; u <= n; ++u)
        for (int v : graph[u]) ++indegree[v];
    std::queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (indegree[i] == 0) q.push(i);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        order.push_back(cur);
        for (int next : graph[cur])
            if (--indegree[next] == 0) q.push(next);
    }
    return order;   // order.size() < n 이면 사이클
}
```

## 상황별 선택

| 문제 유형 | 알고리즘 | 복잡도 |
| --- | --- | --- |
| 가중치 없음, 최단 거리 | BFS | O(V + E) |
| 가중치 0/1 | 0-1 BFS (`std::deque`, 0 은 앞 / 1 은 뒤) | O(V + E) |
| 양수 가중치, 한 점 출발 | Dijkstra | O(E log V) |
| 모든 쌍 최단 거리 (V ≤ 수백) | Floyd–Warshall | O(V³) |
| 연결 요소 / 같은 집합 판정 | DFS·BFS / Union-Find | O(V + E) / ≈ O(1) |
| 최소 비용으로 모두 연결 | Kruskal (MST) | O(E log E) |
| 작업 순서 | 위상 정렬 | O(V + E) |
| 트리에서 두 노드의 공통 조상 | [LCA](../03_algorithms/graph/lca.cpp) | O(log N) / 질의 |
