/*
 * 깊이 우선 탐색 (DFS) & 너비 우선 탐색 (BFS)
 * - DFS: 재귀(스택)로 한 방향을 끝까지 탐색
 * - BFS: 큐로 가까운 노드부터 탐색 (가중치 없는 그래프의 최단 거리)
 * - 시간 복잡도: O(V + E)
 * - 번호가 작은 노드부터 방문하도록 인접 리스트를 정렬한다
 *
 * 입력: 노드 수 N, 간선 수 M, 시작 노드, 이어서 M 줄의 무방향 간선
 * Python 버전: Warming-Up-for-Python/03_algorithms/graph/dfs_bfs.py
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void dfs(const Graph& graph, int cur, std::vector<bool>& visited, std::vector<int>& order) {
    visited[cur] = true;
    order.push_back(cur);
    for (int next : graph[cur]) {
        if (!visited[next]) dfs(graph, next, visited, order);
    }
}

std::vector<int> bfs(const Graph& graph, int start) {
    std::vector<bool> visited(graph.size(), false);
    std::vector<int> order;
    std::queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        const int cur = q.front();
        q.pop();
        order.push_back(cur);
        for (int next : graph[cur]) {
            if (!visited[next]) {
                visited[next] = true;  // 큐에 넣을 때 방문 처리 (중복 삽입 방지)
                q.push(next);
            }
        }
    }
    return order;
}

void print(const std::vector<int>& order) {
    for (std::size_t i = 0; i < order.size(); ++i) std::cout << (i ? " " : "") << order[i];
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, start;
    std::cin >> n >> m >> start;
    Graph graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    for (auto& adj : graph) std::sort(adj.begin(), adj.end());

    std::vector<bool> visited(n + 1, false);
    std::vector<int> dfs_order;
    dfs(graph, start, visited, dfs_order);
    print(dfs_order);
    print(bfs(graph, start));
}

/*
[Input Example 1]
4 5 1
1 2
1 3
1 4
2 4
3 4
[Output Example 1]
1 2 4 3
1 2 3 4
*/
