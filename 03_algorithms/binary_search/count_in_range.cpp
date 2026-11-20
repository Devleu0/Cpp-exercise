/*
 * 정렬된 배열에서 값이 [left_value, right_value] 범위인 원소의 개수
 * - upper_bound(right_value) - lower_bound(left_value)
 * - 시간 복잡도: O(log N)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/binary_search/count_in_range.py
 */
#include <algorithm>
#include <iostream>
#include <vector>

int count_in_range(const std::vector<int>& a, int left_value, int right_value) {
    const auto right_it = std::upper_bound(a.begin(), a.end(), right_value);
    const auto left_it = std::lower_bound(a.begin(), a.end(), left_value);
    return static_cast<int>(right_it - left_it);
}

int main() {
    const std::vector<int> array = {1, 2, 3, 3, 3, 3, 4, 4, 8, 9};

    std::cout << count_in_range(array, 4, 4) << '\n';   // 값이 4 인 원소 개수: 2
    std::cout << count_in_range(array, -1, 3) << '\n';  // 값이 [-1, 3] 인 원소 개수: 6

    // 같은 값의 개수만 필요하면 equal_range 로 한 번에
    const auto [first, last] = std::equal_range(array.begin(), array.end(), 3);
    std::cout << (last - first) << '\n';                // 4
}
