/*
 * 퀵 정렬 (Quick Sort) & 퀵 셀렉트 (Quick Select)
 * - 피벗을 기준으로 작은 값 / 큰 값으로 나눈 뒤 각각 재귀 정렬
 * - 시간 복잡도: 평균 O(N log N), 최악 O(N^2)
 * - 퀵 셀렉트: k 번째로 작은 값을 평균 O(N) 에 찾음
 *   (C++ 에는 같은 역할의 std::nth_element 가 있다)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/sorting/quick_sort.py
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

// 1) 호어(Hoare) 방식 — 첫 원소를 피벗으로, 제자리 정렬
void quick_sort(std::vector<int>& data, int start, int end) {
    if (start >= end) return;
    const int pivot = start;
    int left = start + 1;
    int right = end;
    while (left <= right) {
        while (left <= end && data[left] <= data[pivot]) ++left;      // 피벗보다 큰 값 찾기
        while (right > start && data[right] >= data[pivot]) --right;  // 피벗보다 작은 값 찾기
        if (left > right) {
            std::swap(data[right], data[pivot]);  // 엇갈렸으면 작은 값과 피벗 교체
        } else {
            std::swap(data[left], data[right]);
        }
    }
    quick_sort(data, start, right - 1);
    quick_sort(data, right + 1, end);
}

// 2) 리스트 분할 방식 — 이해하기 쉬운 버전 (추가 메모리 사용)
namespace partition_style {

std::mt19937& rng() {
    static std::mt19937 gen(42);  // 시드 고정: 실행할 때마다 같은 결과
    return gen;
}

int random_pivot(const std::vector<int>& arr) {
    std::uniform_int_distribution<std::size_t> dist(0, arr.size() - 1);
    return arr[dist(rng())];
}

void split(const std::vector<int>& arr, int pivot,
           std::vector<int>& lows, std::vector<int>& pivots, std::vector<int>& highs) {
    for (int x : arr) {
        if (x < pivot) lows.push_back(x);
        else if (x > pivot) highs.push_back(x);
        else pivots.push_back(x);  // 중복 고려
    }
}

// k 번째(1-based)로 작은 값
int quick_select(const std::vector<int>& arr, int k) {
    const int pivot = random_pivot(arr);
    std::vector<int> lows, pivots, highs;
    split(arr, pivot, lows, pivots, highs);

    const int num_lows = static_cast<int>(lows.size());
    const int num_pivots = static_cast<int>(pivots.size());
    if (k <= num_lows) return quick_select(lows, k);
    if (k <= num_lows + num_pivots) return pivot;
    return quick_select(highs, k - num_lows - num_pivots);
}

std::vector<int> quick_sort(const std::vector<int>& arr) {
    if (arr.size() <= 1) return arr;
    const int pivot = random_pivot(arr);
    std::vector<int> lows, pivots, highs;
    split(arr, pivot, lows, pivots, highs);

    std::vector<int> result = quick_sort(lows);
    result.insert(result.end(), pivots.begin(), pivots.end());
    const std::vector<int> sorted_highs = quick_sort(highs);
    result.insert(result.end(), sorted_highs.begin(), sorted_highs.end());
    return result;
}

}  // namespace partition_style

void print(const std::vector<int>& v) {
    std::cout << '[';
    for (std::size_t i = 0; i < v.size(); ++i) std::cout << (i ? ", " : "") << v[i];
    std::cout << "]\n";
}

int main() {
    std::vector<int> data = {8, 5, 4, 7, 2};
    quick_sort(data, 0, static_cast<int>(data.size()) - 1);
    print(data);  // [2, 4, 5, 7, 8]

    const std::vector<int> arr = {5, 3, 2, 4, 1};
    std::cout << partition_style::quick_select(arr, 3) << '\n';  // 3
    print(partition_style::quick_sort(arr));                      // [1, 2, 3, 4, 5]

    // 표준 라이브러리: nth_element 는 k 번째 원소를 제자리에 놓는다 (평균 O(N))
    std::vector<int> copy = arr;
    std::nth_element(copy.begin(), copy.begin() + 2, copy.end());
    assert(copy[2] == 3);
}
