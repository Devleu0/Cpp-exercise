/*
 * 이진 탐색 (Binary Search)
 * - 정렬된 배열에서 탐색 범위를 절반씩 줄여 가며 target 을 찾음
 * - 시간 복잡도: O(log N)
 * - 값이 없으면 -1 반환 (Python 버전의 None 대신)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/binary_search/binary_search.py
 */
#include <cassert>
#include <iostream>
#include <vector>

int binary_search(const std::vector<int>& array, int target) {
    int start = 0;
    int end = static_cast<int>(array.size()) - 1;
    while (start <= end) {
        const int mid = start + (end - start) / 2;  // (start + end) / 2 의 오버플로 방지
        if (array[mid] == target) return mid;
        if (array[mid] > target) {
            end = mid - 1;    // 왼쪽 절반 탐색
        } else {
            start = mid + 1;  // 오른쪽 절반 탐색
        }
    }
    return -1;
}

int main() {
    const std::vector<int> array = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    const int target = 13;

    const int result = binary_search(array, target);
    if (result == -1) {
        std::cout << "None\n";
    } else {
        std::cout << result + 1 << '\n';  // 몇 번째 원소인지 (1-based)
    }

    assert(binary_search(array, 4) == -1);
}
