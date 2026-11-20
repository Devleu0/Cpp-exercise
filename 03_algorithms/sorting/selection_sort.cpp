/*
 * 선택 정렬 (Selection Sort)
 * - 남은 구간에서 가장 작은 값을 골라 맨 앞과 교환하는 것을 반복
 * - 시간 복잡도: O(N^2)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/sorting/selection_sort.py
 */
#include <iostream>
#include <utility>
#include <vector>

void selection_sort(std::vector<int>& data) {
    const int n = static_cast<int>(data.size());
    for (int i = 0; i < n; ++i) {
        int min_index = i;  // 가장 작은 원소의 인덱스
        for (int j = i + 1; j < n; ++j) {
            if (data[min_index] > data[j]) min_index = j;
        }
        std::swap(data[i], data[min_index]);
    }
}

int main() {
    std::vector<int> data = {8, 5, 4, 7, 2};
    selection_sort(data);
    for (int x : data) std::cout << x << '\n';
}
