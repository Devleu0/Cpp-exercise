/*
 * 삽입 정렬 (Insertion Sort)
 * - 앞쪽(이미 정렬된 구간)의 알맞은 위치에 현재 원소를 끼워 넣음
 * - 시간 복잡도: O(N^2), 거의 정렬된 데이터라면 O(N) 에 가까움
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/sorting/insertion_sort.py
 */
#include <iostream>
#include <utility>
#include <vector>

void insertion_sort(std::vector<int>& data) {
    const int n = static_cast<int>(data.size());
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0; --j) {         // j 는 i 부터 1 까지 감소
            if (data[j - 1] > data[j]) {
                std::swap(data[j - 1], data[j]);  // 한 칸씩 앞으로 이동
            } else {
                break;                            // 자기보다 작은 값을 만나면 멈춤
            }
        }
    }
}

int main() {
    std::vector<int> data = {8, 5, 4, 7, 2};
    insertion_sort(data);
    for (int x : data) std::cout << x << '\n';
}
