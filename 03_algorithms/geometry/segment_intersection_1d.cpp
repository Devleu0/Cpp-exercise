/*
 * 1차원 두 선분의 교점(정수 좌표) 개수
 * - 겹치는 구간 = [max(시작), min(끝)]
 * - 개수 = max(min(끝) - max(시작) + 1, 0)
 * - 시간 복잡도: O(1)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/geometry/segment_intersection_1d.py
 */
#include <algorithm>
#include <iostream>
#include <utility>

using Segment = std::pair<int, int>;  // [start, end]

int count_intersections(const Segment& a, const Segment& b) {
    return std::max(std::min(a.second, b.second) - std::max(a.first, b.first) + 1, 0);
}

int main() {
    std::cout << count_intersections({3, 7}, {6, 9}) << '\n';  // 6, 7 → 2
    std::cout << count_intersections({3, 5}, {7, 9}) << '\n';  // 안 겹침 → 0
}
