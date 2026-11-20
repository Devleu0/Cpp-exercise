/*
 * 펜윅 트리 (Fenwick Tree, Binary Indexed Tree)
 * - 점 갱신 / 구간 합: 둘 다 O(log N)
 * - 인덱스는 1 부터 사용, i & -i 는 i 의 최하위 1 비트
 *
 * 예제 2: 역전수(Inversion Count) — 좌표 압축 + 펜윅 트리, O(N log N)
 * Python 버전: Warming-Up-for-Python/03_algorithms/data_structure/fenwick_tree.py
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class FenwickTree {
public:
    explicit FenwickTree(int size) : n_(size), tree_(size + 1, 0) {}

    // i 번째 값에 diff 를 더함
    void update(int i, long long diff) {
        for (; i <= n_; i += (i & -i)) tree_[i] += diff;
    }

    // 1 부터 i 까지의 합
    long long query(int i) const {
        long long res = 0;
        for (; i > 0; i -= (i & -i)) res += tree_[i];
        return res;
    }

    // start 부터 end 까지의 합
    long long interval_sum(int start, int end) const { return query(end) - query(start - 1); }

    // i 번째 값을 value 로 바꿈
    void set(int i, long long value) { update(i, value - interval_sum(i, i)); }

private:
    int n_;
    std::vector<long long> tree_;
};

// ---------------------------------------------------------------
// 예제 1: 값 변경이 섞인 구간 합 쿼리
// ---------------------------------------------------------------
void interval_sum_demo() {
    FenwickTree bit(5);
    const std::vector<int> values = {1, 2, 3, 4, 5};
    for (int i = 1; i <= 5; ++i) bit.set(i, values[i - 1]);

    std::cout << bit.interval_sum(2, 5) << '\n';  // 14
    bit.update(3, -2);                            // 3번째 값 3 -> 1
    std::cout << bit.interval_sum(2, 5) << '\n';  // 12
    bit.update(5, 2);                             // 5번째 값 5 -> 7
    std::cout << bit.interval_sum(2, 5) << '\n';  // 14
    std::cout << bit.interval_sum(1, 5) << '\n';  // 15
}

// ---------------------------------------------------------------
// 예제 2: 역전수 — (i, j) 쌍 중 i < j 이면서 A[i] > A[j] 인 것의 개수
// ---------------------------------------------------------------
long long inversion_count(const std::vector<int>& arr) {
    // 1. 좌표 압축: 값을 1..K 순위로 변환 (1-based)
    std::vector<int> sorted_unique = arr;
    std::sort(sorted_unique.begin(), sorted_unique.end());
    sorted_unique.erase(std::unique(sorted_unique.begin(), sorted_unique.end()), sorted_unique.end());
    const int max_rank = static_cast<int>(sorted_unique.size());

    // 2. 왼쪽부터 보면서 "이미 나온 수 중 나보다 큰 수" 를 센다
    FenwickTree bit(max_rank);
    long long count = 0;
    for (int x : arr) {
        const int rank = static_cast<int>(
            std::lower_bound(sorted_unique.begin(), sorted_unique.end(), x) - sorted_unique.begin()) + 1;
        count += bit.query(max_rank) - bit.query(rank);  // 전체 - (나 이하) = 나보다 큰 수
        bit.update(rank, 1);
    }
    return count;
}

int main() {
    interval_sum_demo();

    const std::vector<int> data = {5, 3, 1, 4, 2};
    const long long result = inversion_count(data);
    std::cout << "입력 배열: [5, 3, 1, 4, 2], 역전수: " << result << '\n';
    assert(result == 7);  // (5,3) (5,1) (5,4) (5,2) (3,1) (3,2) (4,2)
}
