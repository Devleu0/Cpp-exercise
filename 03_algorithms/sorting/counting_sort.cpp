/*
 * 계수 정렬 (Counting Sort)
 * - 값의 범위가 작을 때, 각 값의 등장 횟수를 세어 순서대로 출력
 * - 시간 복잡도: O(N + K)  (K: 최댓값)
 * - 값이 0 이상의 정수이고 범위가 작을 때만 사용 가능
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/sorting/counting_sort.py
 */
#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> counting_sort(const std::vector<int>& data) {
    if (data.empty()) return {};
    const int max_value = *std::max_element(data.begin(), data.end());
    std::vector<int> count(max_value + 1, 0);  // 모든 값의 범위를 담을 수 있는 크기
    for (int x : data) ++count[x];

    std::vector<int> sorted;
    sorted.reserve(data.size());
    for (int value = 0; value <= max_value; ++value) {
        for (int k = 0; k < count[value]; ++k) sorted.push_back(value);  // 등장한 횟수만큼
    }
    return sorted;
}

int main() {
    const std::vector<int> data = {8, 5, 4, 7, 2};
    for (int x : counting_sort(data)) std::cout << x << '\n';
}
