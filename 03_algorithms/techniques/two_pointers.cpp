/*
 * 투 포인터 (Two Pointers) — 합이 M 인 연속 구간의 개수
 * - start 를 한 칸씩 옮기면서, 구간 합이 M 이상이 될 때까지 end 를 늘린다
 * - 모든 원소가 양수일 때만 성립
 * - 시간 복잡도: O(N)
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/techniques/two_pointers.py
 */
#include <iostream>
#include <vector>

int count_subarrays_with_sum(const std::vector<int>& data, int m) {
    const int n = static_cast<int>(data.size());
    int count = 0;
    int interval_sum = 0;
    int end = 0;

    for (int start = 0; start < n; ++start) {
        while (interval_sum < m && end < n) {  // end 를 가능한 만큼 오른쪽으로
            interval_sum += data[end];
            ++end;
        }
        if (interval_sum == m) ++count;
        interval_sum -= data[start];           // start 를 한 칸 이동
    }
    return count;
}

int main() {
    const std::vector<int> data = {1, 2, 3, 2, 5};
    std::cout << count_subarrays_with_sum(data, 5) << '\n';  // [2,3] [3,2] [5] → 3
}
