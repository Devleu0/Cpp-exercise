/*
 * 최장 증가 부분 수열 (LIS, Longest Increasing Subsequence) — O(N log N)
 * - tails[i] = 길이가 i+1 인 증가 부분 수열들의 마지막 원소 중 최솟값
 * - tails 는 항상 오름차순 → lower_bound 로 x 가 들어갈 위치를 찾는다
 * - 주의: tails 자체가 실제 LIS 수열은 아니다 (길이만 유효)
 * - 비감소(<=) 수열이 필요하면 lower_bound 대신 upper_bound
 *
 * Python 버전: Warming-Up-for-Python/03_algorithms/dp/lis.py
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int lis_length(const std::vector<int>& nums) {
    std::vector<int> tails;
    for (int x : nums) {
        const auto it = std::lower_bound(tails.begin(), tails.end(), x);  // x 이상인 첫 위치
        if (it == tails.end()) {
            tails.push_back(x);  // 모든 LIS 의 끝보다 크다 → 길이 연장
        } else {
            *it = x;             // 같은 길이의 끝 값을 더 작은 값으로 갱신
        }
    }
    return static_cast<int>(tails.size());
}

int main() {
    const std::vector<int> data = {10, 9, 2, 5, 3, 7, 101, 18};

    std::cout << "입력 수열: [10, 9, 2, 5, 3, 7, 101, 18]\n";
    const int result = lis_length(data);
    std::cout << "LIS 길이: " << result << '\n';  // 4 ([2, 3, 7, 18] 등)

    assert(result == 4);
    assert(lis_length({}) == 0);
}
