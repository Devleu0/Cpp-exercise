/*
 * 단절점 (Articulation Point, Cut Vertex)
 * - DFS 방문 순서(order)와, 자손이 back-edge 로 도달 가능한 가장 빠른 순서(low)를 비교
 * - 루트가 아닌 노드: 자식의 low >= 내 order 이면 단절점
 * - 루트 노드: DFS 트리 자식이 2 개 이상이면 단절점
 * - 시간 복잡도: O(V + E)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/graph/articulation_point.py
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

class ArticulationPoint {
public:
    explicit ArticulationPoint(const std::vector<std::vector<int>>& adj)
        : adj_(adj), order_(adj.size(), 0) {
        for (int i = 1; i < static_cast<int>(adj.size()); ++i) {
            if (order_[i] == 0) dfs(i, true);
        }
    }

    // 정렬된 단절점 목록
    std::vector<int> result() const { return {cut_vertex_.begin(), cut_vertex_.end()}; }

private:
    int dfs(int cur, bool is_root) {
        order_[cur] = ++cnt_;
        int low = order_[cur];
        int child_count = 0;

        for (int next : adj_[cur]) {
            if (order_[next] != 0) {
                low = std::min(low, order_[next]);  // 이미 방문한 노드 (back-edge)
                continue;
            }
            ++child_count;
            const int child_low = dfs(next, false);
            // 자식이 우회로로 내 조상(더 작은 순서)에 갈 수 없으면 나는 단절점
            if (!is_root && child_low >= order_[cur]) cut_vertex_.insert(cur);
            low = std::min(low, child_low);
        }

        if (is_root && child_count >= 2) cut_vertex_.insert(cur);
        return low;
    }

    const std::vector<std::vector<int>>& adj_;
    std::vector<int> order_;  // 방문 순서
    int cnt_ = 0;
    std::set<int> cut_vertex_;
};

int main() {
    // 1-2-3 연결, 2-4 연결 → 2 를 지우면 {1}, {3}, {4} 로 끊어짐
    const int n = 4;
    const std::vector<std::pair<int, int>> edges = {{1, 2}, {2, 3}, {2, 4}};
    std::vector<std::vector<int>> adj(n + 1);
    for (const auto& [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);  // 무방향 그래프
    }

    const ArticulationPoint ap(adj);
    const auto cut = ap.result();
    std::cout << "단절점 목록: [";
    for (std::size_t i = 0; i < cut.size(); ++i) std::cout << (i ? ", " : "") << cut[i];
    std::cout << "]\n";  // [2]

    assert((cut == std::vector<int>{2}));
}
