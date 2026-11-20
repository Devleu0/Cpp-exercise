/*
 * 위상 정렬 (Topological Sort) — Kahn 알고리즘
 * - 진입 차수가 0 인 노드를 큐에 넣고, 꺼낼 때마다 연결된 간선을 제거
 * - 시간 복잡도: O(V + E)
 * - 결과 길이가 V 보다 작으면 사이클이 존재 → 빈 벡터 반환
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/graph/topological_sort.py
 */
#include <cassert>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using Graph = std::vector<std::vector<int>>;

std::vector<int> topological_sort(const Graph& adj) {
    const int n = static_cast<int>(adj.size()) - 1;  // 노드는 1..n
    std::vector<int> indegree(n + 1, 0);
    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) ++indegree[v];  // 1. 진입 차수 계산
    }

    std::queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) q.push(i);     // 2. 진입 차수 0 인 노드 삽입
    }

    std::vector<int> result;
    while (!q.empty()) {                      // 3. 큐가 빌 때까지
        const int cur = q.front();
        q.pop();
        result.push_back(cur);
        for (int next : adj[cur]) {
            if (--indegree[next] == 0) q.push(next);
        }
    }

    if (static_cast<int>(result.size()) != n) return {};  // 사이클 존재
    return result;
}

Graph build(int n, const std::vector<std::pair<int, int>>& edges) {
    Graph adj(n + 1);
    for (const auto& [u, v] : edges) adj[u].push_back(v);
    return adj;
}

int main() {
    // 1 -> 2, 1 -> 5, 2 -> 3, 3 -> 4, 5 -> 2, 6 (독립)
    const Graph adj = build(6, {{1, 2}, {1, 5}, {2, 3}, {3, 4}, {5, 2}});
    const auto order = topological_sort(adj);

    std::cout << "위상 정렬 결과: [";
    for (std::size_t i = 0; i < order.size(); ++i) std::cout << (i ? ", " : "") << order[i];
    std::cout << "]\n";  // [1, 6, 5, 2, 3, 4]

    // 사이클: 1 -> 2 -> 3 -> 1
    assert(topological_sort(build(3, {{1, 2}, {2, 3}, {3, 1}})).empty());
}
