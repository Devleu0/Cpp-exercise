/*
 * 서로소 집합 (Disjoint Set, Union-Find)
 * - find  : 루트 노드 찾기 (경로 압축)
 * - unite : 두 집합 합치기 (더 작은 번호가 루트가 되도록)
 * - 시간 복잡도: 거의 O(1) (경로 압축 시 평균 α(N))
 *
 * 입력: 노드 수 V, 합집합 연산 수 E, 이어서 E 줄의 (a, b)
 * Python 버전: Warming-Up-for-Python/03_algorithms/data_structure/disjoint_set.py
 */
#include <iostream>
#include <numeric>
#include <vector>

class DisjointSet {
public:
    explicit DisjointSet(int n) : parent_(n + 1) {
        std::iota(parent_.begin(), parent_.end(), 0);  // 처음엔 자기 자신이 부모
    }

    int find(int x) {
        if (parent_[x] != x) parent_[x] = find(parent_[x]);  // 경로 압축
        return parent_[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a < b) {
            parent_[b] = a;
        } else {
            parent_[a] = b;
        }
    }

    bool same(int a, int b) { return find(a) == find(b); }

    int parent(int x) const { return parent_[x]; }

private:
    std::vector<int> parent_;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int v, e;
    std::cin >> v >> e;
    DisjointSet ds(v);
    for (int i = 0; i < e; ++i) {
        int a, b;
        std::cin >> a >> b;
        ds.unite(a, b);
    }

    std::cout << "Root nodes for all nodes: ";
    for (int i = 1; i <= v; ++i) std::cout << ds.find(i) << ' ';
    std::cout << '\n';

    std::cout << "Parent Table: ";
    for (int i = 1; i <= v; ++i) std::cout << ds.parent(i) << ' ';
    std::cout << '\n';
}

/*
[Input Example 1]
6 4
1 4
2 3
2 4
5 6
[Output Example 1]
Root nodes for all nodes: 1 1 1 1 5 5
Parent Table: 1 1 1 1 5 5
*/
