/*
 * 다익스트라 최단 경로 (Dijkstra)
 * - 우선순위 큐에서 거리가 가장 짧은 노드를 꺼내 인접 노드의 거리를 갱신
 * - 시간 복잡도: O(E log V)
 * - 음수 가중치가 있으면 사용할 수 없다
 * - std::priority_queue 는 최대 힙 → greater<> 로 최소 힙을 만든다
 *
 * 입력: 노드 수 N, 간선 수 M, 시작 노드, 이어서 M 줄의 (a, b, c): a→b 비용 c
 * Python 버전: Warming-Up-for-Python/03_algorithms/graph/dijkstra.py
 */
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

constexpr long long INF = 1e18;

using Edge = std::pair<int, int>;  // (도착 노드, 비용)
using Graph = std::vector<std::vector<Edge>>;

std::vector<long long> dijkstra(const Graph& graph, int start) {
    std::vector<long long> dist(graph.size(), INF);
    using Item = std::pair<long long, int>;  // (거리, 노드) — 거리가 먼저여야 거리순 정렬
    std::priority_queue<Item, std::vector<Item>, std::greater<>> pq;

    dist[start] = 0;
    pq.emplace(0, start);
    while (!pq.empty()) {
        const auto [d, now] = pq.top();
        pq.pop();
        if (dist[now] < d) continue;  // 이미 더 짧은 경로로 처리된 노드
        for (const auto& [next, cost] : graph[now]) {
            const long long new_dist = d + cost;
            if (new_dist < dist[next]) {
                dist[next] = new_dist;
                pq.emplace(new_dist, next);
            }
        }
    }
    return dist;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, start;
    std::cin >> n >> m >> start;
    Graph graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        graph[a].emplace_back(b, c);
    }

    const auto dist = dijkstra(graph, start);
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF) {
            std::cout << "INFINITY\n";
        } else {
            std::cout << dist[i] << '\n';
        }
    }
}

/*
[Input Example 1]
5 6
1
5 1 1
1 2 2
1 3 3
2 3 4
2 4 5
3 4 6
[Output Example 1]
0
2
3
7
INFINITY
*/
