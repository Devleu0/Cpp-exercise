/*
 * 최소 신장 트리 (MST) — 크루스칼 알고리즘 (Kruskal)
 * - 간선을 비용 오름차순으로 정렬하고, 사이클이 생기지 않으면 선택 (Union-Find)
 * - 시간 복잡도: O(E log E)
 *
 * 입력: 노드 수 V, 간선 수 E, 이어서 E 줄의 (a, b, cost)
 * Python 버전: Warming-Up-for-Python/03_algorithms/graph/mst.py
 */
#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

class DisjointSet {
public:
    explicit DisjointSet(int n) : parent_(n + 1) { std::iota(parent_.begin(), parent_.end(), 0); }

    int find(int x) { return parent_[x] == x ? x : parent_[x] = find(parent_[x]); }

    // 합쳤으면 true, 이미 같은 집합(사이클)이면 false
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (a < b) {
            parent_[b] = a;
        } else {
            parent_[a] = b;
        }
        return true;
    }

private:
    std::vector<int> parent_;
};

using WeightedEdge = std::tuple<int, int, int>;  // (비용, a, b) — 비용이 먼저여야 비용순 정렬

long long kruskal(int v, std::vector<WeightedEdge> edges) {
    std::sort(edges.begin(), edges.end());
    DisjointSet ds(v);
    long long total = 0;
    for (const auto& [cost, a, b] : edges) {
        if (ds.unite(a, b)) total += cost;  // 사이클이 생기지 않을 때만 포함
    }
    return total;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int v, e;
    std::cin >> v >> e;
    std::vector<WeightedEdge> edges;
    edges.reserve(e);
    for (int i = 0; i < e; ++i) {
        int a, b, cost;
        std::cin >> a >> b >> cost;
        edges.emplace_back(cost, a, b);
    }
    std::cout << kruskal(v, std::move(edges)) << '\n';
}

/*
[Input Example 1]
7 9
1 2 29
1 5 75
2 3 35
2 6 34
3 4 7
4 6 23
4 7 13
5 6 53
6 7 25
[Output Example 1]
159
*/
