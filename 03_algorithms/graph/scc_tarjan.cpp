/*
 * 강한 연결 요소 (SCC, Strongly Connected Components) — 타잔 알고리즘 (Tarjan)
 * - DFS 방문 순서(d)와 스택을 이용해, 자기 자신보다 위로 올라갈 수 없는 노드를 SCC 의 루트로 판정
 * - 시간 복잡도: O(V + E)
 * - SCC 는 위상 정렬의 역순으로 발견된다
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/graph/scc_tarjan.py
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

class TarjanSCC {
public:
    explicit TarjanSCC(const std::vector<std::vector<int>>& adj)
        : adj_(adj), d_(adj.size(), 0), finished_(adj.size(), false) {
        for (int i = 1; i < static_cast<int>(adj.size()); ++i) {
            if (d_[i] == 0) dfs(i);
        }
    }

    const std::vector<std::vector<int>>& result() const { return scc_; }

private:
    int dfs(int u) {
        d_[u] = ++id_;  // 방문 순서 기록
        stack_.push_back(u);

        int parent = d_[u];
        for (int v : adj_[u]) {
            if (d_[v] == 0) {
                parent = std::min(parent, dfs(v));  // 1. 아직 방문하지 않은 이웃
            } else if (!finished_[v]) {
                parent = std::min(parent, d_[v]);   // 2. 방문했지만 SCC 미확정(스택에 있음) → 사이클
            }
        }

        if (parent == d_[u]) {                       // 3. 위로 올라갈 수 없음 → SCC 발견
            std::vector<int> component;
            while (true) {
                const int t = stack_.back();
                stack_.pop_back();
                finished_[t] = true;
                component.push_back(t);
                if (t == u) break;
            }
            std::sort(component.begin(), component.end());
            scc_.push_back(std::move(component));
        }
        return parent;
    }

    const std::vector<std::vector<int>>& adj_;
    int id_ = 0;
    std::vector<int> d_;           // 방문 순서 (discovery time)
    std::vector<bool> finished_;   // SCC 확정 여부
    std::vector<int> stack_;
    std::vector<std::vector<int>> scc_;
};

int main() {
    // 1 -> 2 -> 3 -> 1 (사이클: 1,2,3)
    // 3 -> 4 -> 5 -> 4 (사이클: 4,5)
    // 5 -> 6           (독립: 6)
    const int n = 6;
    const std::vector<std::pair<int, int>> edges = {{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 5}, {5, 4}, {5, 6}};
    std::vector<std::vector<int>> adj(n + 1);
    for (const auto& [u, v] : edges) adj[u].push_back(v);

    const TarjanSCC solver(adj);
    const auto& scc = solver.result();

    std::cout << "찾은 SCC 개수: " << scc.size() << '\n';
    std::cout << "SCC 구성: [";
    for (std::size_t i = 0; i < scc.size(); ++i) {
        std::cout << (i ? ", " : "") << '[';
        for (std::size_t j = 0; j < scc[i].size(); ++j) std::cout << (j ? ", " : "") << scc[i][j];
        std::cout << ']';
    }
    std::cout << "]\n";  // [[6], [4, 5], [1, 2, 3]]

    assert(scc.size() == 3);
}
