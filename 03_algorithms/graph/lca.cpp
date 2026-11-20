/*
 * 최소 공통 조상 (LCA, Lowest Common Ancestor) — Binary Lifting
 * - parent[k][v] = v 의 2^k 번째 조상
 * - 점화식: parent[k][v] = parent[k-1][ parent[k-1][v] ]
 * - 전처리 O(N log N), 질의 O(log N)
 * - 루트는 1 번 노드
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/graph/lca.py
 */
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

class LCA {
public:
    static constexpr int MAX_LOG = 20;  // 2^20 > 1,000,000

    LCA(int n, const std::vector<std::vector<int>>& adj)
        : n_(n), depth_(n + 1, 0), parent_(MAX_LOG, std::vector<int>(n + 1, 0)) {
        std::vector<bool> visited(n + 1, false);
        dfs(adj, 1, 0, visited);  // 1. 깊이와 직계 부모(parent[0]) 계산
        fill_parent();            // 2. 희소 배열 채우기
    }

    int get(int a, int b) const {
        if (depth_[a] > depth_[b]) std::swap(a, b);  // b 가 더 깊도록

        for (int k = MAX_LOG - 1; k >= 0; --k) {     // 1. 깊이 맞추기
            if (depth_[b] - depth_[a] >= (1 << k)) b = parent_[k][b];
        }
        if (a == b) return a;                        // 2. 이미 같다면 그게 LCA

        for (int k = MAX_LOG - 1; k >= 0; --k) {     // 3. 공통 조상 바로 아래까지 함께 올리기
            if (parent_[k][a] != parent_[k][b]) {
                a = parent_[k][a];
                b = parent_[k][b];
            }
        }
        return parent_[0][a];                        // 4. 바로 위가 LCA
    }

private:
    // 재귀 깊이가 N 까지 갈 수 있다. 일자 트리처럼 깊이가 매우 크면 반복문(스택)으로 바꿀 것
    void dfs(const std::vector<std::vector<int>>& adj, int cur, int d, std::vector<bool>& visited) {
        visited[cur] = true;
        depth_[cur] = d;
        for (int next : adj[cur]) {
            if (visited[next]) continue;
            parent_[0][next] = cur;
            dfs(adj, next, d + 1, visited);
        }
    }

    void fill_parent() {
        for (int k = 1; k < MAX_LOG; ++k) {
            for (int v = 1; v <= n_; ++v) parent_[k][v] = parent_[k - 1][parent_[k - 1][v]];
        }
    }

    int n_;
    std::vector<int> depth_;
    std::vector<std::vector<int>> parent_;
};

int main() {
    /*
     *       1
     *     /   \
     *    2     3
     *   / \   /
     *  4   5 6
     */
    const int n = 6;
    const std::vector<std::pair<int, int>> edges = {{1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}};
    std::vector<std::vector<int>> adj(n + 1);
    for (const auto& [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    const LCA lca(n, adj);
    std::cout << "LCA(4, 5) -> " << lca.get(4, 5) << '\n';  // 2
    std::cout << "LCA(4, 6) -> " << lca.get(4, 6) << '\n';  // 1
    std::cout << "LCA(3, 6) -> " << lca.get(3, 6) << '\n';  // 3

    assert(lca.get(5, 5) == 5);
}
